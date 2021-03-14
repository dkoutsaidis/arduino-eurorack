#include "CustomLCD.h"

const float userBPM = 60.0;
const int userTimeSignatureForStep = 4; // {4, 8, 16, 32}

const float bpmToHz = 1.0 / 60.0;
float userBPMms = (1.0 / (userBPM * bpmToHz)) * 1000.0 / float(userTimeSignatureForStep / 4);

const int channelPins[] = {13};
bool stepsGrid[] = {true, false, false, false,
                    true, false, false, false,
                    true, false, false, false,
                    true, false, false, false};

int numChannels = sizeof(channelPins) / sizeof(channelPins[0]);
int numSteps = sizeof(stepsGrid) / sizeof(stepsGrid[0]);

void playStep(int pin, float pulseWidthHalf, bool shouldPlay) {
  digitalWrite(pin, shouldPlay);
  delay(pulseWidthHalf);
  digitalWrite(pin, LOW);
  delay(pulseWidthHalf);
}

void setup() { 
  for (int iChannel = 0; iChannel < numChannels; ++iChannel) {
    pinMode(channelPins[iChannel], OUTPUT);
  }
  
  setupCustomChars();
  lcd.begin(16, 2);
  lcd.clear();
  printInitInfo(userBPM, numSteps);
  printAllSteps(stepsGrid, numSteps);
}

void loop() {  
  for (int iStep = 0; iStep < numSteps; ++iStep) {
    printAllSteps(stepsGrid, numSteps);
    setActiveStep(iStep, stepsGrid[iStep]);
    
    playStep(channelPins[0], userBPMms / 2, stepsGrid[iStep]);
  }
}
