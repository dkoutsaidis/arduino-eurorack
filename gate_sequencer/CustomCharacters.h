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

byte StepOnActive[8] = {
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

byte StepOffActive[8] = {
  B00000,
  B11111,
  B10001,
  B10001,
  B10001,
  B11111,
  B11111,
};

#endif
