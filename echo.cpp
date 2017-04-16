#include "effects.hpp"




void Echo::setD(uint32_t _D){
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
    DryWet = _DryWet;
}
float Echo::getDryWet(){
    return DryWet;
}

Echo::Echo(float _Td, float _Fb, float _DryWet){
		setTd(_Td);
    setFb(_Fb);
		setDryWet(_DryWet);
    delayed_sample = new int16_t[3*D];

}
Echo::Echo(uint32_t _D, float _Fb, float _DryWet){
		setD(_D);
    setFb(_Fb);
		setDryWet(_DryWet);
    delayed_sample = new int16_t[3*D+1];

}
Echo::~Echo(){
    delete [] delayed_sample;

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

	Echo* myEcho = new Echo((uint32_t)40, 0.5f, 0.1f);
	myEcho->setFb(0.5f);

	int lenArray = 125;

	int16_t inputArray[lenArray];
	int16_t outputArray[lenArray];

	for (int i = 0; i < lenArray; i++) {
		if (  i < 1 ){
			inputArray[i] = 1000;
		}
		else{
			inputArray[i] = 0;
		}

		outputArray[i] = myEcho->echoCompute(inputArray[i]);
	}

	saveArrayToFile(argv[1], inputArray, lenArray);
	saveArrayToFile(argv[2], outputArray, lenArray);

	return 0;
}
