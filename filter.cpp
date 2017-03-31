#include "filter.h"


void Filter::setType(filtType newFilterType){
  filterType = newFilterType;
}
void Filter::setFc(uint32_t newFc){
  Fc = newFc;
}
void Filter::setBandwidth(uint32_t newBw){
  bw = newBw;
}
void Filter::setQ(float newQ){
  Q = newQ;
}
void Filter::setOrder(uint32_t newOrder){
  order = newOrder;
}
void Filter::setFs(uint32_t newFs){
  Fs = newFs;
}



//getter
filtType Filter::getType(){
  return filterType;
}
uint32_t Filter::getFc(){
  return Fc;
}
uint32_t Filter::getBandwidth(){
  return bw;
}
float Filter::getQ(){
  return Q;
}
uint32_t Filter::getOrder(){
  return order;
}

void Filter::DesignLPF(void){
  coeff[0] = 0.5f*(1.0f-cos(wc));
  coeff[1] = 1.0f-cos(wc);
  coeff[2] = coeff[0];
  coeff[3] = 1.0f + alpha;
  coeff[4] = -2.0f*cos(wc);
  coeff[5] = 1.0f - alpha;
}

void Filter::DesignHPF(void){
}

void Filter::DesignBPF(void){
}

Filter::Filter(uint32_t _Fs){
  setOrder(DEFAULT_ORDER);
  setFc(DEFAULT_FC);
  setQ(DEFAULT_Q);
  setType(LPF);
  setFs(_Fs);

  wc = 2*M_PI*( ((float)Fc)/((float)Fs) );
  alpha = 0.5f*( sin(wc / Q ));

  DesignLPF();

}
Filter::Filter(filtType _filterType, uint32_t _Fc, uint32_t _Fs, uint32_t _order, float _Q){
  setOrder(_order);
  setFc(_Fc);
  setQ(_Q);
  setType(_filterType);
  setFs(_Fs);
  // set intermediate variables

  wc = 2*M_PI*( ((float)Fc)/((float)Fs) );
  alpha = 0.5f*( sin(wc / Q ));

  switch(_filterType){
    case LPF :
      DesignLPF();
    case HPF :
      DesignHPF();
  }
}

Filter::Filter(filtType _filterType, uint32_t _Fc, uint32_t _Fs, uint32_t _order, uint32_t _bw){
  setOrder(_order);
  setFc(_Fc);
  setBandwidth(_bw);
  setType(_filterType);
  setFs(_Fs);
  // set intermediate variables
  wc = 2*M_PI*( ((float)Fc)/((float)Fs) );
  alpha =  sin(wc)*sinh(0.5f*log(2)*bw*(wc/sin(wc)));

  switch(_filterType){
    case BPF :
      DesignBPF();
  }
}

Filter::~Filter(){

}



int main(void){
  Filter myLPF(SAMPLE_RATE);
  myLPF.coeff[0] = 0.3f;
  for (int i = 0; i < 6; i++) {
    cout << myLPF.coeff[i] << endl;
  }
  cout << myLPF.wc << " | "<< myLPF.alpha << endl;
  return 0;
}
