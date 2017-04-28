#include <cmath>
#include <iostream>
#include <fstream>
#include "effects.hpp"
#include "global.hpp"

void Echo::setD(uint32_t _D) {
    if(_D > MAX_DELAY){
				cout << "Maximum delay is 5 sec" << endl;
        D = MAX_DELAY;
    }
    else{
        D = _D;
    }

}

uint32_t Echo::getD(){
	return D;
}

void Echo::setFb(float _Fb){
    Fb = _Fb;
}
float Echo::getFb(){
    return Fb;
}

void Echo::setTd(float _Td){
	Td = _Td;
	setD((uint32_t)(SAMPLE_RATE*Td));
}

float Echo::getTd(){
	return Td;
}

void Echo::setDryWet(float _DryWet){
    if (_DryWet < 0) {DryWet = 0;}
    else if (_DryWet > 1) {DryWet = 1;}
    else {DryWet = _DryWet;}

}
float Echo::getDryWet(){
    return DryWet;
}

void Echo::setStatus(uint32_t _status){
  if (_status > 0){
    status = ON;
  }
  else{
    status = OFF;
  }
}
uint32_t Echo::getStatus(){
  return status;
}

Echo::Echo(float _Td, float _Fb, float _DryWet){
		setTd(_Td);
    setFb(_Fb);
		setDryWet(_DryWet);
    setStatus(OFF);
    delayed_sample = new int16_t[3*D+1];

}
Echo::Echo(uint32_t _D, float _Fb, float _DryWet){
		setD(_D);
    setFb(_Fb);
		setDryWet(_DryWet);
    setStatus(OFF);
    delayed_sample = new int16_t[3*D+1];

}
Echo::~Echo(){
    delete [] delayed_sample;

}
int16_t Echo::echoEffect (int16_t input){
  if(status == ON){
    return ( (int16_t)(DryWet*input +(1-DryWet)*echoComputev2(input)) );
  }
  else{
    return input;
  }
}

int16_t Echo::echoCompute (int16_t input){

    static unsigned int i = 0;
    shiftSamples(input);

    if (i < D){
      i++;
			return 0;

		}
		else {
			return (int16_t) (Fb*delayed_sample[2*D]+ pow((double)Fb,2.0f)*delayed_sample[D] + pow((double)Fb,3.0f)*delayed_sample[0] )  ;
		}
	}

int16_t Echo::echoComputev2 (int16_t input){

    static unsigned int i = 0;
    storeSamples(input, i%(3*D+1));
    i++;

    if (i < D){
			return 0;
		}
		else {
			return (int16_t) (Fb*delayed_sample[(2*D+i)%(3*D+1)]+ pow((double)Fb,2.0f)*delayed_sample[(D+i)%(3*D+1)] + pow((double)Fb,3.0f)*delayed_sample[i%(3*D+1)] )  ;
		}
	}


void Echo::shiftSamples (int16_t input){

    for(uint32_t i = 0; i< 3*D+1; i++){
        if (i == 3*D ) {
            delayed_sample[i] = input;
        }
        else{
            delayed_sample[i] = delayed_sample[i+1];
        }
	}
}

void Echo::storeSamples(int16_t input, uint32_t i){
    delayed_sample[3*D-i] = input;
}


/*
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

int main(int argc, char* argv[]){

	Echo* myEcho = new Echo((uint32_t)40, 1.5f, 0.1f);
	myEcho->setFb(0.5f);
  myEcho->setDryWet(0.9f);
  myEcho->setStatus(ON);

	int lenArray = 125;

	int16_t inputArray[lenArray];
	int16_t outputArray[lenArray];
  double sum = 0;

	for (int i = 0; i < lenArray; i++) {
		if (  i < 1 ){
			inputArray[i] = 1000;
		}
		else{
			inputArray[i] = 0;
		}
    clock_t begin = clock();
		outputArray[i] = myEcho->echoEffect(inputArray[i]);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    sum += elapsed_secs;
	}
  double avg_elapsed_secs = sum/lenArray;
  cout << "Average execution time of echoEffect function : " << avg_elapsed_secs << " s." << endl;

	saveArrayToFile(argv[1], inputArray, lenArray);
	saveArrayToFile(argv[2], outputArray, lenArray);

	return 0;
}
*/
