#ifndef OSCILLATORS_H
#define OSCILLATORS_H

#define RES (1024)
#define PHASE_FACTOR  ((float)RES/(float)SAMPLE_RATE) // factor between the phase and the array index
#define DEFAULT_WF (wavetable_sine)
#define DEFAULT_FREQ (440)

class Osc {
public:
  Osc();
  Osc(int16_t * _wavetable, uint32_t _frequency);
  ~Osc();
  void setFrequency(uint32_t _frequency);
  int16_t process();
  void reset();
private:
  int16_t linearInterpolation();
  int16_t * wavetable;
  uint32_t phase;
  uint32_t frequency;
  int16_t value;
};

#endif
