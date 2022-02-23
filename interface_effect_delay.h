#ifndef interface_effect_delay_h_
#define interface_effect_delay_h_

#include <math.h>
#include "Arduino.h"
#include "AudioStream.h"
#include "InterfaceEffect.h"

#define DELAY_LINE_LEN 1

class InterfaceEffectDelay : public InterfaceEffect
{
public:
	InterfaceEffectDelay() : InterfaceEffect(false, false) {
        memset(delayLineL, 0, sizeof(delayLineL));
		delayLineIndex = 0;
    }

	virtual void update(audio_block_t* blockL, audio_block_t* blockR);

private:
	float delayLineL[(int) (AUDIO_SAMPLE_RATE * DELAY_LINE_LEN)];
	int delayLineIndex;	
	
	float inputL;
	
	float dryWetMix = 0.5;
};

#endif
