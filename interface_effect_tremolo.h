#ifndef interface_effect_tremolo_h_
#define interface_effect_tremolo_h_

#include <math.h>
#include "Arduino.h"
#include "AudioStream.h"

class InterfaceEffectTremolo : public AudioStream
{
public:
	InterfaceEffectTremolo() : AudioStream(numChannels, inputQueueArray) {
        for(int i = 0; i < AUDIO_SAMPLE_RATE; i++) {
            wavetable[i] = sin(2 * M_PI * i / AUDIO_SAMPLE_RATE);
        }
    }

	virtual void update(void);

private:
    float wavetable[(int)(AUDIO_SAMPLE_RATE)];
	int wtIndex;
	
	float input;
	
	float dryWetMix = 0.5;
	
	int count = 0;
	bool on = true;
	
	const static int numChannels = 1;
	audio_block_t *inputQueueArray[numChannels];
};

#endif
