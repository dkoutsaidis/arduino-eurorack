#ifndef CUSTOM_CHARACTERS_H
#define CUSTOM_CHARACTERS_H

#include "Arduino.h"

byte StepOn[8] = {
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
};

byte StepOff[8] = {
  B00000,
  B11111,
  B10001,
  B10001,
  B10001,
  B11111,
  B00000,
};

byte StepOnActive[8];
byte StepOffActive[8];

void createActiveCharacter(byte* newActiveArray, byte* referenceArray, int arraySize)
{
  memcpy(newActiveArray, referenceArray, arraySize);
  newActiveArray[7] = B11111;
}

#endif
