#include "effects.hpp"


uint16_t Echo::getD(){
	return D;
}

void Echo:setD(uint16_t _D){
	D = _D;
}

Echo:Echo(uint16_t _D, float _G, float _DryWet){
	setD(_D);
	
}

Echo:~Echo(){
		
}

int16_t Echo::delayCompute (int16_t input){
	
	static int i = 0;
	static int16_t delayed_sample[MAX_DELAY];
	
	shiftSamples(delayed_sample, input);

	if (i < Echo.D){
		i++;
		return input;
	}
	else{
		return input + (int16_t)(delayed_sample[0]);
	}
}


void Echo::shiftSamples (int16_t delayed_sample[], int16_t input){
	
	for(int i = 0; i< Echo.D; i++){
		if (i == (Echo.D - 1) ) {
			delayed_sample[i] = input;
		}
		else{
		delayed_sample[i] = delayed_sample[i-1];
		}
	}
	
}