const float userBPM = 120.0;
const float bpmToHz = 1.0 / 60.0;
float userBPMms = (1.0 / (userBPM * bpmToHz)) * 1000.0;

const int cvSteps[] = {6, 7, 8, 9, 10, 11, 12, 13};
const int numSteps = sizeof(cvSteps) / sizeof(cvSteps[0]);
const int startStep = cvSteps[0];
const int endStep = cvSteps[numSteps - 1];

void stepOver(int pinToEnable, int pinToDisable) {
  digitalWrite(pinToDisable, LOW);
  digitalWrite(pinToEnable, HIGH);
}

void debugPrint(int numSteps, int currentStep) {
  Serial.print("|");
  
  for (int iStep = 0; iStep < numSteps; ++iStep)
    Serial.print(String(currentStep == iStep) + "|");
    
  Serial.println();
}
void setup() { 
  Serial.begin(9600);
  
  for (int iStep = 0; iStep < numSteps; ++iStep) {
    pinMode(cvSteps[iStep], OUTPUT);
  }
}

void loop() {
  for (int currentStep = startStep; currentStep <= endStep; ++currentStep) {
    stepOver(currentStep, currentStep != startStep ? currentStep - 1 : endStep);
    debugPrint(numSteps, currentStep - startStep);
    delay(userBPMms);
  }

  Serial.println();
}
