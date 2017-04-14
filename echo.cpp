#include "effects.hpp"

uint32_t Echo::getD(){
	return D;
}
float Echo::getFb(){
    return Fb;
}

void Echo::setD(uint32_t _D){
    if(_D > MAX_DELAY){
        D = MAX_DELAY;
    }
    else{
        D = _D;
    }

}

void Echo::setFb(float _Fb){
    Fb = _Fb;
}

Echo::Echo(uint32_t _D, float _Fb, float _DryWet){
	setD(_D);
    setFb(_Fb);
    delayed_sample = new int16_t[3*D];
	
}

Echo::~Echo(){
    delete [] delayed_sample;
		
}

int16_t Echo::echoCompute (int16_t input){
	
    static unsigned int i = 0;

	
    shiftSamples(input);

    if (i < D){
		i++;
		return input;
	}
	else{
        return input + (int16_t) (Fb*delayed_sample[2*D]+ pow((double)Fb,2.0f)*delayed_sample[D] + pow((double)Fb,3.0f)*delayed_sample[0] )  ;
	}
}


void Echo::shiftSamples (int16_t input){
	
    for(uint32_t i = 0; i< 3*D; i++){
        if (i == (3*D - 1) ) {
			delayed_sample[i] = input;
		}
		else{
            delayed_sample[i] = delayed_sample[i+1];
		}
	}
}
