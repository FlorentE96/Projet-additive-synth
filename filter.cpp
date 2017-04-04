#include "filter.hpp"

// ************ TODO : verify designed filter **********************************

void Filter::setTypeInit(filtType newFilterType){
  filterType = newFilterType;
}

void Filter::setType( filtType newFilterType) {
  filterType = newFilterType;
  DesignFilter( filterType );
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
void Filter::setFs(){
  Fs = SAMPLE_RATE;
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

float Filter::getCoeff(uint32_t i){
  return coeff[i];
}

void Filter::DesignFilter( filtType _filterType ){

	  /*switch(_filterType){
    case LPF :
      cout << "LPF" << endl;
      DesignLPF();
    case HPF :
    cout << "HPF" << endl;
      DesignHPF();
  }*/

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

  coeff[0] = 0.5f*(1.0f-cos(wc));
  coeff[1] = 1.0f-cos(wc);
  coeff[2] = coeff[0];
  coeff[3] = 1.0f + alpha;
  coeff[4] = -2.0f*cos(wc);
  coeff[5] = 1.0f - alpha;
}

void Filter::DesignHPF(void){

  coeff[0] = 0.5f*(1.0f+cos(wc));
  coeff[1] = -1.0f-cos(wc);
  coeff[2] = coeff[0];
  coeff[3] = 1.0f + alpha;
  coeff[4] = -2.0f*cos(wc);
  coeff[5] = 1.0f - alpha;
}

void Filter::DesignBPF(void){

  coeff[0] = Q*alpha;
  coeff[1] = 0.0f;
  coeff[2] = -coeff[0];
  coeff[3] = 1.0f + alpha;
  coeff[4] = -2.0f*cos(wc);
  coeff[5] = 1.0f - alpha;
}

Filter::Filter(){
  setOrder(DEFAULT_ORDER);
  setFc(DEFAULT_FC);
  setQ(DEFAULT_Q);
  setTypeInit(LPF);
  setFs();

  wc = 2*M_PI*( ((float)Fc)/((float)Fs) );
  alpha = 0.5f*( sin(wc / Q ));

  DesignLPF();

}
Filter::Filter(filtType _filterType, uint32_t _Fc, float _Q, uint32_t _order ){
  setOrder(_order);
  setFc(_Fc);
  setQ(_Q);
  setTypeInit(_filterType);
  setFs();
  // set intermediate variables

  wc = 2*M_PI*( ((float)Fc)/((float)Fs) );
  alpha = 0.5f*( sin(wc / Q ));

  DesignFilter( filterType );


}

Filter::Filter(filtType _filterType, uint32_t _Fc, float _Q, uint32_t _bw, uint32_t _order){
  setOrder(_order);
  setFc(_Fc);
  setQ(_Q);
  setBandwidth(_bw);
  setTypeInit(_filterType);
  setFs();

  // set intermediate variables
  wc = 2*M_PI*( ((float)Fc)/((float)Fs) );
  alpha =  sin(wc)*sinh(0.5f*log(2.0f)*bw*(wc/sin(wc)));

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
  static int16_t inputs[2];
  static int16_t outputs[2];
  static int i = 0;

  if (i < 2 ){
    outputs[i] = 0;
    inputs[i] = idata;
    i++;
  }
  else{
    result = (int16_t)( (coeff[0]/coeff[3])*idata + (coeff[1]/coeff[3])*inputs[1] + (coeff[2]/coeff[3])*inputs[0] - (coeff[4]/coeff[3])*outputs[1] - (coeff[5]/coeff[3])*outputs[0] );
    outputs[0] = outputs[1];
    outputs[1] = result;
    inputs[0] = inputs[1];
    inputs[1] = idata;
  }
  return result;
}

bool loadArrayFromFile(const char* filename, int16_t* array, uint32_t lenArray){

    string STRING;
    ifstream file;
    file.open(filename);
    if(file.is_open()){
        for (uint32_t i = 0; i < lenArray; i++) {
          getline(file,STRING);
          array[i] = (int16_t)atoi(STRING.c_str());
        }
        file.close();
        return true;
    }
    else{
        return false;
    }

}

int getLenArrayFromFile(const char* filename){
  string STRING;
  ifstream file;
  file.open(filename);
  if(file.is_open()){
      int i = 0;
      while(file.eof() == 0){
        getline(file,STRING);
        i++;
      }
      file.close();
      return i;
  }
  cout << "Erreur d'ouverture fichier" << endl;
  return -1;
}


bool saveArrayToFile(const char* filename, int16_t* array, uint32_t lenArray){

    ofstream file;
    file.open(filename);
    file.flush();
    if(file.is_open()){
        for (uint32_t i = 0; i < lenArray -1; i++) {
          file <<  array[i] << endl;
        }
        file.close();
        return true;
    }
    else{
        return false;
    }
}

//int main(int argc, char* argv[]){

//  Filter myFilter(LPF, 2000, 1.0f, 2);

//  int lenArray = getLenArrayFromFile(argv[1]);
//  int16_t inputArray[lenArray];
//  loadArrayFromFile(argv[1], inputArray, lenArray);


//  int16_t outputArray[lenArray];
//  for (int i = 0; i < lenArray; i++) {
//    outputArray[i] = myFilter.filterCompute(inputArray[i]);
//  }
//  saveArrayToFile(argv[2], outputArray, lenArray);

//  return 0;
//}
