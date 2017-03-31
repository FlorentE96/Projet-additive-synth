#ifndef OSCILLATORS_H
#define OSCILLATORS_H

#define RES (1024)
#define PHASE_FACTOR  ((float)RES/(float)SAMPLE_RATE) // factor between the phase and the array index

typedef enum {SINE = 0, TRIANGLE, SAW, SQUARE, USER} Waveform;

class Osc {
public:
  Osc();
  Osc(Waveform _wf, int _frequency);
  ~Osc();
  int16_t process();
private:
  linearInterpolation();
};

#endif
