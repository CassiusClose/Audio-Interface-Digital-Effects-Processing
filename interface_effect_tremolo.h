#ifndef interface_effect_tremolo_h_
#define interface_effect_tremolo_h_

#include <math.h>
#include "Arduino.h"
#include "AudioStream.h"
#include "InterfaceEffect.h"

class InterfaceEffectTremolo : public InterfaceEffect
{
public:
	InterfaceEffectTremolo() : InterfaceEffect(true, false) {
        for(int i = 0; i < AUDIO_SAMPLE_RATE; i++) {
            wavetable[i] = sin(2 * M_PI * i / AUDIO_SAMPLE_RATE);
        }
    }

	virtual void update(audio_block_t* blockL, audio_block_t* blockR);

private:
    float wavetable[(int)(AUDIO_SAMPLE_RATE)];
	int wtIndex;
	
	float input;
	
	float dryWetMix = 0.5;
};

#endif
