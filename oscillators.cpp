#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdint>
#include "global.h"
#include "oscillators.h"
#include "LUTs.h"
using namespace std;

Osc::Osc() {
  phase = 0;
  frequency = DEFAULT_FREQUENCY;
  value = 0;
  wavetable = DEFAULT_WF;
}

Osc::Osc(int16_t * _wavetable, uint32_t _frequency) {
  phase = 0;
  frequency = _frequency;
  value = 0;
  wavetable = _wavetable;
}

Osc::~Osc() {
  //
}

int16_t Osc::process() {
  phase += frequency; // increment the phasor
  if(phase >= SAMPLE_RATE) // normalize
    phase -= SAMPLE_RATE;
  value = linearInterpolation();
  return value;
}

void Osc::reset() {
  phase = 0;
  value = 0;
}

int16_t Osc::linearInterpolation() {
  float temp = phase * PHASE_FACTOR; // Scales the phase to LUT resolution
  int16_t intPart = temp; // int part of the scaled phasor
  float fracPart = temp-intPart; // fractional part
  int16_t sample0 = wavetable[intPart]; // first sample
  if(++intPart >= RES) // modulo
    intPart = 0;
  int16_t sample1 = wavetable[intPart]; //second sample
  return sample0 + (sample1 - sample0) * fracPart; //interpolation
}

int main(void)
{
  float _length = 0.5f; // 1.8s of "sound"
  Osc sine_osc(wavetable_saw3, DEFAULT_FREQ);
  ofstream outputFile;
  outputFile.open("out_wt.csv", std::ofstream::out | std::ofstream::trunc);
  if (outputFile.is_open())
  {
      for(int i=0; i<(int)(_length*SAMPLE_RATE); i++) // main sample calculation loop
      {
        outputFile << sine_osc.process() << endl;
      }
  }
  else
    cout << "Impossible d'ouvrir le fichier " << endl;

}
