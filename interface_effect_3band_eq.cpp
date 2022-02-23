#include <Arduino.h>
#include "interface_effect_3band_eq.h"

void InterfaceEffectDelay::update(void)
{
	audio_block_t *block = receiveWritable(0);

    if(!block)
        return;

	lp_biquad lowpass;
	hp_biquad highpass;
	float hp_cutoff=4000;
	float lp_cutoff=500;
	float Q=15;	
	lowpass.set(lp_cutoff,Q);
	highpass.set(hp_cutoff,Q);

    for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
		
		input = block->data[i];
		low=lowpass.doBiquad(input);
		high=highpass.doBiquad(input);
		mid=input-low-high;
		block->data[i] = (low*lowcoeff+high*highcoeff+mid*midcoeff)*dryWetMix+ (1-dryWetMix)*input;
		
		
    }

    transmit(block, 0);
    release(block);
}