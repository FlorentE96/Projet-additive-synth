#include "filter.hpp"


void Filter::setType_Init(filtType newFilterType){
  filterType = newFilterType;
}

void Filter::setFc_Init(uint32_t newFc){
  Fc = newFc;
}
void Filter::setBandwidth_Init(uint32_t newBw){
  bw = newBw;
}
void Filter::setQ_Init(double newQ){
  Q = newQ;
}
void Filter::setOrder_Init(uint32_t newOrder){
  order = newOrder;
}
void Filter::setFs_Init(){
  Fs = SAMPLE_RATE;
}



void Filter::setType( filtType newFilterType) {
  filterType = newFilterType;
  DesignFilter( filterType );
}
void Filter::setFc(uint32_t newFc){
  Fc = newFc;
  DesignFilter( filterType );
}
void Filter::setBandwidth(uint32_t newBw){
  bw = newBw;
  DesignFilter( filterType );
}
void Filter::setQ(double newQ){
  Q = newQ;
  DesignFilter( filterType );
}
void Filter::setOrder(uint32_t newOrder){
  order = newOrder;
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
double Filter::getQ(){
  return Q;
}
uint32_t Filter::getOrder(){
  return order;
}

double Filter::getCoeff(uint32_t i){
  return coeff[i];
}



void Filter::DesignFilter( filtType _filterType ){

  if(_filterType == LPF){
  DesignLPF();
  }
  else if(_filterType == HPF){
  DesignHPF();
  }
  else if (_filterType == BPF){
    DesignBPF();
  }

}
void Filter::DesignLPF(void){

  cout << "LPF" << endl;

  wc = 2*M_PI*( ((double)Fc)/((double)Fs) );
  alpha = 0.5*( sin(wc / Q ));


  coeff[0] = 0.5*(1.0-cos(wc));
  coeff[1] = 1.0-cos(wc);
  coeff[2] = coeff[0];
  coeff[3] = 1.0 + alpha;
  coeff[4] = -2.0*cos(wc);
  coeff[5] = 1.0 - alpha;



}

void Filter::DesignHPF(void){


  wc = 2*M_PI*( ((double)Fc)/((double)Fs) );
  alpha = 0.5*( sin(wc / Q ));


  coeff[0] = 0.5*(1.0+cos(wc));
  coeff[1] = -1.0-cos(wc);
  coeff[2] = coeff[0];
  coeff[3] = 1.0 + alpha;
  coeff[4] = -2.0*cos(wc);
  coeff[5] = 1.0 - alpha;

}

void Filter::DesignBPF(void){

  cout << "BPF" << endl;

  wc = 2*M_PI*( ((double)Fc)/((double)Fs) );
  alpha =  (double)( sin(wc)/(2*Q)); //sinh( (0.5*log(2.0)*bw*(wc/sin(wc)) ) ));

  coeff[0] = Q*alpha;
  coeff[1] = 0.0;
  coeff[2] = -coeff[0];
  coeff[3] = 1.0 + alpha;
  coeff[4] = -2.0*cos(wc);
  coeff[5] = 1.0 - alpha;



}

Filter::Filter(){
  setOrder_Init(DEFAULT_ORDER);
  setFc_Init(DEFAULT_FC);
  setQ_Init(DEFAULT_Q);
  setType_Init(LPF);
  setFs_Init();

  DesignLPF();

}
Filter::Filter(filtType _filterType, uint32_t _Fc, double _Q, uint32_t _order ){
  setOrder_Init(_order);
  setFc_Init(_Fc);
  setQ_Init(_Q);
  setType_Init(_filterType);
  setFs_Init();

  DesignFilter( filterType );


}

Filter::Filter(filtType _filterType, uint32_t _Fc, double _Q, uint32_t _bw, uint32_t _order){
  setOrder_Init(_order);
  setFc_Init(_Fc);
  setQ_Init(_Q);
  setBandwidth_Init(_bw);
  setType_Init(_filterType);
  setFs_Init();

  DesignFilter( filterType );
}

Filter::~Filter(){

}

void Filter::filterArrayCompute(int16_t* iarray, int16_t* oarray, uint32_t iLen){
  for(uint32_t i = 0; i < iLen; i++){
      if(i<2){
        oarray[i] = 0;
      }
      else {
        oarray[i] =(int16_t)( (coeff[0]/coeff[3])*iarray[i] + (coeff[1]/coeff[3])*iarray[i-1] + (coeff[2]/coeff[3])*iarray[i-2] - (coeff[4]/coeff[3])*oarray[i-1] - (coeff[5]/coeff[3])*oarray[i-2] );
      }

  }

}

int16_t Filter::filterCompute(int16_t idata){
  int16_t result = 0;
  /***** filterX_samples structure *****/
  /***** | input[0] | input[1] | output[0] | output[1] | ****/
  /***** there are sample redundance between the stages  => optimization to be done ****/
  static int16_t filter1_samples[4];
  static int16_t filter2_samples[4];
  static int i = 0;
  int16_t input = idata;



  if (i < 2 ){
    filter1_samples[i] = 0;
    filter1_samples[i+2] = input;
    filter2_samples[i] = 0;
    filter2_samples[i+2] = 0;
    result = 0;
    i++;
  }
  else{

        result = (int16_t)( (coeff[0]/coeff[3])*input + (coeff[1]/coeff[3])*filter1_samples[3] + (coeff[2]/coeff[3])*filter1_samples[2] - (coeff[4]/coeff[3])*filter1_samples[1] - (coeff[5]/coeff[3])*filter1_samples[0] );
        filter1_samples[0] = filter1_samples[1];
        filter1_samples[1] = result;
        filter1_samples[2] = filter1_samples[3];
        filter1_samples[3] = input;


        if(getOrder() == 4 ){
            input = result; // output is now input for the next 2nd order filter
            result = (int16_t)( (coeff[0]/coeff[3])*input + (coeff[1]/coeff[3])*filter2_samples[3] + (coeff[2]/coeff[3])*filter2_samples[2] - (coeff[4]/coeff[3])*filter2_samples[1] - (coeff[5]/coeff[3])*filter2_samples[0] );
            filter2_samples[0] = filter2_samples[1];
            filter2_samples[1] = result;
            filter2_samples[2] = filter2_samples[3];
            filter2_samples[3] = input;
        }
  }
  return result;
}


