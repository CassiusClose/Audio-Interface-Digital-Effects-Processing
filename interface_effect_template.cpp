#include <Arduino.h>
#include "interface_effect_delay.h"

void InterfaceEffectDelay::update(void)
{
	audio_block_t *block = receiveWritable(0);

    if(!block)
        return;


    for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
		
    }


    transmit(block, 0);
    release(block);
}


