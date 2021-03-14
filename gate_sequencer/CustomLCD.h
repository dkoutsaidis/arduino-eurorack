#ifndef CUSTOM_LCD_H
#define CUSTOM_LCD_H

#include "Arduino.h"
#include "CustomCharacters.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setupCustomChars()
{
  createActiveCharacter(StepOnActive, StepOn, sizeof(StepOn));
  createActiveCharacter(StepOffActive, StepOff, sizeof(StepOff));

  createFinalCharacter(StepOnFinal, StepOn, sizeof(StepOn));
  createFinalCharacter(StepOffFinal, StepOff, sizeof(StepOff));

  lcd.createChar(0, StepOff);
  lcd.createChar(2, StepOffActive);
  lcd.createChar(4, StepOffFinal);
  
  lcd.createChar(1, StepOn);
  lcd.createChar(3, StepOnActive);
  lcd.createChar(5, StepOnFinal);
}

void printInitInfo(float userBPM, int numSteps)
{
  lcd.setCursor(0, 0);
  lcd.print("BPM:" + String(int(userBPM)));

  lcd.setCursor(8, 0);
  lcd.print("Steps:" + String(numSteps));

  delay(5000);
}

void printAllSteps(bool* stepsGrid, int numSteps, int userSteps)
{
  lcd.setCursor(0, 1);
  for (int iStep = 0; iStep < numSteps; ++iStep)
  {
    int currentValue = int(stepsGrid[iStep]);
    lcd.write(byte(iStep == userSteps ? currentValue + 4 : currentValue));
  }
}

void setActiveStep(int position, bool state)
{
  lcd.setCursor(position, 1);
  lcd.write(byte(int(state) + 2));
}

void updateBMP(int newValue)
{
  String newValueChars = String(newValue);
  lcd.setCursor(4, 0);
  lcd.print(String(newValue));

  if (newValueChars.length() == 2)
  {
    lcd.setCursor(6, 0);
    lcd.print(" ");
  }
}

#endif
