#ifndef GATE_SEQUENCER_HELPERS_H
#define GATE_SEQUENCER_HELPERS_H

#include "Arduino.h"

float bpmToMs(float bpm)
{
  const float bpmToHz = 1.0 / 60.0;
  return (1.0 / (bpm * bpmToHz)) * 1000.0;
}

#endif
