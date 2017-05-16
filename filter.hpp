#ifndef FILTER_H
#define FILTER_H

#include <cstdint>
#include <cmath>
#include "global.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#define DEFAULT_FC (1000)
#define DEFAULT_Q (1.0f)
#define DEFAULT_ORDER (2)

using namespace std;

// idee : créer un template pour travailler en float ou double

enum filtType {LPF, HPF, BPF};

class Filter{
private:
  float coeff[6];   //6 coefficients for biquad filter design
  filtType filterType; //lowpass, bandpass, highpass
  uint32_t Fc; //cut-off frequency or center frequency for BPF case
  uint32_t bw;
  uint32_t order; //filter order (2 or 4)
  float Q; //quality factor

  void DesignFilter(filtType _filterType);
  
  // filling filter coefficients array regarding filter type and parameters given
  void DesignLPF(void);
  void DesignHPF(void);
  void DesignBPF(void);

  void setType_Init(filtType newFilterType);
  void setFc_Init(uint32_t newFc);
  void setBandwidth_Init(uint32_t newBw);
  void setQ_Init(float newQ);
  void setOrder_Init(uint32_t newOrder);


public:

  //constructors
  Filter();

  Filter(filtType _filterType, uint32_t _Fc, float _Q, uint32_t _order);
  Filter(filtType _filterType, uint32_t _Fc, float _Q, uint32_t _bw, uint32_t _order);

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
  float getCoeff(uint32_t i);

  //other functions
  int16_t filterCompute(int16_t idata);

};


#endif
