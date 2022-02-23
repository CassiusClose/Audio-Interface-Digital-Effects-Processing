#include <Arduino.h>
#include "interface_effect_delay.h"

void InterfaceEffectDelay::update(void)
{
	audio_block_t *blockL = receiveWritable(0);

    if(!blockL)
        return;
	
	/*audio_block_t *blockR = receiveWritable(1);
	
	if(!blockR) {
		release(blockL);
		return;
	}*/


    for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
		
		inputL = blockL->data[i];
		
		blockL->data[i] *= (1 - dryWetMix) + dryWetMix * delayLineL[delayLineIndex];
		
		delayLineL[delayLineIndex] = inputL;
		
		/*
		inputR = blockR->data[i];
		blockR->data[i] *= (1 - dryWetMix) + dryWetMix * delayLineR[delayLineIndex];
		delayLineR[delayLineIndex] = inputR;*/
		
		delayLineIndex++;
		if(delayLineIndex >= AUDIO_SAMPLE_RATE * DELAY_LINE_LEN)
			delayLineIndex = 0;
    }

    transmit(blockL, 0);
	//transmit(blockR, 1);
    release(blockL);
	//release(blockR);
}


