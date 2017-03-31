#include <cstdint>
#include <cmath>
#include "global.h"
#include <iostream>

#define DEFAULT_FC (1000)
#define DEFAULT_Q (1.0f)
#define DEFAULT_ORDER (2)

using namespace std;

// idee : créer un template pour travailler en float ou double

enum filtType {LPF, HPF, BPF};

class Filter{
private:


  filtType filterType; //lowpass, bandpass, highpass
  uint32_t Fc; //cut-off frequency or center frequency for BPF case
  uint32_t Fs; //sampling frequency
  uint32_t bw;
  uint32_t order; //filter order (2 or 4)
  float Q; //quality factor

  // filling filter coefficients array regarding filter type and parameters given
  void DesignLPF(void);
  void DesignHPF(void);
  void DesignBPF(void);
  void setFs(uint32_t NewFs);


public:
    float coeff[6];   //6 coefficients for biquad filter design
    float alpha;
    float wc; //normalized cut-off frequency
  //constructors
  Filter(uint32_t _Fs);

  Filter(filtType _filterType, uint32_t _Fc, uint32_t _Fs, uint32_t _order, float _Q);
  Filter(filtType _filterType, uint32_t _Fc, uint32_t _Fs, uint32_t _order, uint32_t _bw);


  //destructors
  ~Filter();

  //setter
  void setType(filtType newFilterType);
  void setFc(uint32_t newFc);
  void setBandwidth(uint32_t newBw);
  void setQ(float newQ);
  void setOrder(uint32_t newOrder);

  //getter
  filtType getType();
  uint32_t getFc();
  uint32_t getBandwidth();
  float getQ();
  uint32_t getOrder();

  //other functions
  /*uint16_t filterCompute(uint16_t sampledata);
  bool saveArrayToFile(const char* filename, uint16_t* values, int values_len);
  bool loadArrayFromFile(const char* filename, uint16_t* values, int values_len);*/




};
