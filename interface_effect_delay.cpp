#include <Arduino.h>
#include "interface_effect_delay.h"

void InterfaceEffectDelay::update(void)
{
	audio_block_t *block = receiveWritable(0);

    if(!block)
        return;

    for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
		
		input = block->data[i];
		
		block->data[i] = block->data[i] * (1 - dryWetMix) + dryWetMix * delayLine[delayLineIndex];
		
		delayLine[delayLineIndex] = input;
		
		delayLineIndex++;
		if(delayLineIndex >= AUDIO_SAMPLE_RATE * DELAY_LINE_LEN)
			delayLineIndex = 0;
    }

    transmit(block, 0);
    release(block);
}


