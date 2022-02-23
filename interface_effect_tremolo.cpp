#include <Arduino.h>
#include "interface_effect_tremolo.h"

void InterfaceEffectTremolo::update(audio_block_t* blockL, audio_block_t* blockR)
{
    for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        blockL->data[i] *= wavetable[wtIndex];
		blockR->data[i] *= wavetable[wtIndex];
		wtIndex++;
		if(wtIndex == AUDIO_SAMPLE_RATE)
			wtIndex = 0;
    }
}


