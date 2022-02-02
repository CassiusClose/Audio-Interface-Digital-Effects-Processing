#include <Arduino.h>
#include "interface_effect_tremolo.h"

void InterfaceEffectTremolo::update(void)
{
	audio_block_t *block = receiveWritable(0);

    if(!block)
        return;

    for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        block->data[i] *= wavetable[wtIndex];
		wtIndex++;
		if(wtIndex == AUDIO_SAMPLE_RATE)
			wtIndex = 0;
	
		count++;
		if(count > 22050) {
			count = 0;
			on = !on;
		}
    }

    transmit(block, 0);
    release(block);
}


