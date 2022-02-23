#include <Arduino.h>
#include "interface_effect_tremolo.h"

void InterfaceEffectTremolo::update(void)
{
	audio_block_t *blockL = receiveWritable(0);

    if(!blockL)
        return;
	
	audio_block_t *blockR = receiveWritable(1);
	
	if(!blockR) {
		release(blockL);
		return;
	}

    for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        blockL->data[i] *= wavetable[wtIndex];
		blockR->data[i] *= wavetable[wtIndex];
		wtIndex++;
		if(wtIndex == AUDIO_SAMPLE_RATE)
			wtIndex = 0;
    }

    transmit(blockL, 0);
	transmit(blockR, 1);
    release(blockL);
	release(blockR);
}


