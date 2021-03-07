const float userBPM = 120.0;
const float userDutyCyclePercentage = 0.1; // [0, 1] for HIGH state
const int userTimeSignatureForStep = 16; // {4, 8, 16, 32}

const float bpmToHz = 1.0 / 60.0;
float userBPMms = (1.0 / (userBPM * bpmToHz)) * 1000.0 / float(userTimeSignatureForStep / 4);

const int channelPins[] = {13};
const bool stepsGrid[] = {true, false, false, true,
                          false, true, false, true,
                          true, false, false, true,
                          true, false, false, false};

int numChannels = sizeof(channelPins) / sizeof(channelPins[0]);
int numSteps = sizeof(stepsGrid) / sizeof(stepsGrid[0]);

void playStep(int pin, float pulseWidthHigh, float pulseWidthLow, bool shouldPlay) {
  digitalWrite(pin, shouldPlay);
  delay(pulseWidthHigh);
  digitalWrite(pin, LOW);
  delay(pulseWidthLow);
}

void setup() {
  Serial.begin(9600);
  
  for (int iChannel = 0; iChannel < numChannels; ++iChannel) {
    pinMode(channelPins[iChannel], OUTPUT);
  }
}

void loop() {
  for (int iStep = 0; iStep < numSteps; ++iStep) {
    Serial.println(String(iStep + 1) + "/" + String(numSteps) + ": " + (stepsGrid[iStep] ? "ON" : "OFF"));
    playStep(channelPins[0], userBPMms * userDutyCyclePercentage, userBPMms * (1.0 - userDutyCyclePercentage), stepsGrid[iStep]);
  }

  Serial.println();
}
