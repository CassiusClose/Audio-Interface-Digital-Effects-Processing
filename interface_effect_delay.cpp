#include <Arduino.h>
#include "interface_effect_delay.h"

void InterfaceEffectDelay::update(audio_block_t* blockL, audio_block_t* blockR)
{
    for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
		
		inputL = blockL->data[i];
		
		blockL->data[i] = blockL->data[i] * (1 - dryWetMix) + dryWetMix * delayLineL[delayLineIndex];
		
		delayLineL[delayLineIndex] = inputL;
		
		delayLineIndex++;
		if(delayLineIndex >= AUDIO_SAMPLE_RATE * DELAY_LINE_LEN)
			delayLineIndex = 0;
    }
}


