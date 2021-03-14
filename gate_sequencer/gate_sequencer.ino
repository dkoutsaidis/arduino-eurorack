#include "CustomLCD.h"

float userBPM = 60.0;
const float bpmToHz = 1.0 / 60.0;
float userBPMms = (1.0 / (userBPM * bpmToHz)) * 1000.0;

const int channelPins[] = {13};
bool stepsGrid[] = {true, false, false, false,
                    true, false, false, false,
                    true, false, false, false,
                    true, false, false, false};

int numChannels = sizeof(channelPins) / sizeof(channelPins[0]);
int numSteps = sizeof(stepsGrid) / sizeof(stepsGrid[0]);

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
  printInitInfo(userBPM, numSteps);
  printAllSteps(stepsGrid, numSteps);
}

void loop()
{
  unsigned long currentTime = millis();

  // step forward
  if (currentTime - moveStepPreviousTime >= moveStepTime)
  {
    iStep = (iStep == numSteps - 1) ? 0 : iStep + 1;
    
    printAllSteps(stepsGrid, numSteps);
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
}
