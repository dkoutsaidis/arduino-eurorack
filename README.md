# arduino-eurorack
This repo will host varius arduino-based eurorack modules. The current testing device is an [Arduino Uno REV3](https://store.arduino.cc/arduino-uno-rev3).

- [CV Sequencer](#cv-sequencer)
- [Gate Sequencer](#gate-sequencer)

## CV Sequencer
Single-channel, 8-step CV Sequencer

## Gate Sequencer
Single-channel, multi-step Gate Sequencer

It uses the [LiquidCrystal](https://www.arduino.cc/en/Reference/LiquidCrystal) arduino library, for printing various info and the sequencer's steps to a 16x2 16pin LCD.

<img width="740" alt="current_schematic" src="https://user-images.githubusercontent.com/24361657/111071493-18962a80-84df-11eb-9a1c-fddf0f6d543e.png">

The Digital PIN 13 is used for the output gate sequence (0V-5V, 50% Duty Cycle).
