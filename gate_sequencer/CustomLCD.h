#ifndef CUSTOM_LCD_H
#define CUSTOM_LCD_H

#include "Arduino.h"
#include <LiquidCrystal.h>

byte StepOn[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
};

byte StepOff[8] = {
  B11111,
  B10001,
  B10001,
  B10001,
  B10001,
  B11111,
  B00000,
};

byte StepOnActive[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

byte StepOffActive[8] = {
  B11111,
  B10001,
  B10001,
  B10001,
  B10001,
  B11111,
  B11111,
};

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setupCustomChars()
{
  lcd.createChar(0, StepOff);
  lcd.createChar(2, StepOffActive);
  lcd.createChar(1, StepOn);
  lcd.createChar(3, StepOnActive);
}

void printInitInfo(float userBPM, int numSteps)
{
  lcd.setCursor(0, 0);
  lcd.print("BPM:" + String(int(userBPM)));

  lcd.setCursor(8, 0);
  lcd.print("Steps:" + String(numSteps));

  delay(10000);
}

void printAllSteps(bool stepsGrid[], int numSteps)
{
  lcd.setCursor(0, 1);
  for (int iStep = 0; iStep < numSteps; ++iStep)
  {
    lcd.write(byte(int(stepsGrid[iStep])));
  }
}

void setActiveStep(int position, bool state)
{
  lcd.setCursor(position, 1);
  lcd.write(byte(int(state) + 2));
}

#endif
