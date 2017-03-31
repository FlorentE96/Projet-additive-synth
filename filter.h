#include <stdint>


enum filtType {LPF, HPF, BPF};

//

// filter object (biquad)

class Filter{
private:
  float coeff[6]; //6 coefficients for biquad filter design
  filtType ftype; //lowpass, bandpass, highpass
  uint32_t Fc; //cut-off frequency or center frequency for BPF case
  uint32_t Fs; //sampling frequency
  uint32_t order; //filter order (2 or 4)
  float Q; //quality factor

public:
  //setter
  setFilterType(filtType newFIlterType )

  //getter
  filtType getFilterType();


  //constructors
  Filter();
  Filter(filtType filterType, uint32_t Fc, uint32_t Fs, float Q); //default order 2
  Filter(filtType filterType, uint32_t Fc, uint32_t Fs, uint32_t order, float Q);
  Filter(filtType filterType, uint32_t Fc, uint32_t Fs, uint32_t order, uint32_t bw);

  //destructors
  ~Filter();







};
