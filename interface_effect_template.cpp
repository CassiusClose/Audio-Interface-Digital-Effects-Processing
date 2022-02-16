#include <Arduino.h>
#include "interface_effect_template.h"

void InterfaceEffectTemplate::update(void)
{
	audio_block_t *blockL = receiveWritable(0);

    if(!blockL)
        return;



	audio_block_t *blockR = receiveWritable(0);

    if(!blockR) {
        release(blockL);
        return;
    }



    for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
		
    }


    transmit(blockL, 0);
    transmit(blockR, 1);
    release(blockL);
    release(blockR);
}


