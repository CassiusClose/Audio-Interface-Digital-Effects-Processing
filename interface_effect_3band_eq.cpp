#include <Arduino.h>
#include "interface_effect_3band_eq.h"

void InterfaceEffectEQ::update(audio_block_t* blockL, audio_block_t* blockR)
{
	
	
	
	float hp_cutoff=4000;
	float lp_cutoff=1000;
	float Q=15;	
	lowpass.set(lp_cutoff,Q);
	highpass.set(hp_cutoff,Q);

    for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
		input = blockL->data[i]*0.25;
		low=lowpass.doBiquad(input);
		high=highpass.doBiquad(input);
		mid=input-low-high;
		blockL->data[i] = (low*lowcoeff+high*highcoeff+mid*midcoeff);
		blockR->data[i]=0;
		
		// blockR->data[i] = (low*lowcoeff+high*highcoeff+mid*midcoeff)/2;
		// *dryWetMix+ (1-dryWetMix)*input;s
		// *lowcoeff+high*highcoeff+mid*midcoeff;

		
    }
}
