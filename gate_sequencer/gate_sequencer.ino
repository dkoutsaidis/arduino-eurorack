#include "CustomLCD.h"
#include "GateSequencerHelpers.h"

const float minBPM = 30.0;
const float maxBPM = 240.0;
const int minSteps = 1;
const int maxSteps = 16;

float userBPM = 60.0;
float userBPMms = bpmToMs(userBPM);

int channelPins[] = {13};
bool stepsGrid[] = {true, false, false, false,
                    true, false, false, false,
                    true, false, false, false,
                    true, false, false, false};

int numChannels = sizeof(channelPins) / sizeof(channelPins[0]);
int numSteps = sizeof(stepsGrid) / sizeof(stepsGrid[0]);
int userSteps = numSteps;

unsigned long flipPulseStateTime = userBPMms / 2;
unsigned long flipPulseStatePreviousTime = 0;
unsigned long moveStepTime = userBPMms;
unsigned long moveStepPreviousTime = 0;
int iStep = -1;
bool iState = false;

void setup()
{
  for (int iChannel = 0; iChannel < numChannels; ++iChannel)
  {
    pinMode(channelPins[iChannel], OUTPUT);
  }
  
  setupCustomChars();
  lcd.begin(16, 2);
  lcd.clear();
  printInitInfo(userBPM, userSteps);
  printAllSteps(stepsGrid, numSteps, userSteps);
}

void loop()
{
  unsigned long currentTime = millis();

  // step forward
  if (currentTime - moveStepPreviousTime >= moveStepTime)
  {
    iStep = (iStep > userSteps - 2) ? 0 : iStep + 1;
    
    printAllSteps(stepsGrid, numSteps, userSteps);
    setActiveStep(iStep, stepsGrid[iStep]);
    
    moveStepPreviousTime = currentTime;
  }
  
  // flip the state of the pulse for each step
  if (currentTime - flipPulseStatePreviousTime >= flipPulseStateTime)
  {
    digitalWrite(channelPins[0], !iState ? stepsGrid[iStep] : LOW);
    
    iState = !iState;
    
    flipPulseStatePreviousTime = currentTime;
  }

  // update BPM and related vars
  userBPM = float(int(round(minBPM + analogRead(A0) * ((maxBPM - minBPM) / 1023.0))));
  userBPMms = bpmToMs(userBPM);
  flipPulseStateTime = userBPMms / 2;
  moveStepTime = userBPMms;
  updateBMP(userBPM);

  // update Steps and related vars
  userSteps = int(round(minSteps + analogRead(A1) * ((maxSteps - minSteps) / 1023.0)));
  updateSteps(userSteps);
}
