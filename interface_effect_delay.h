#ifndef interface_effect_delay_h_
#define interface_effect_delay_h_

#include <math.h>
#include "Arduino.h"
#include "AudioStream.h"

#define DELAY_LINE_LEN 1

class InterfaceEffectDelay : public AudioStream
{
public:
	InterfaceEffectDelay() : AudioStream(numChannels, inputQueueArray) {
        memset(delayLineL, 0, sizeof(delayLineL));
		delayLineIndex = 0;
    }

	virtual void update(void);

private:
	float delayLineL[(int) (AUDIO_SAMPLE_RATE * DELAY_LINE_LEN)];
	int delayLineIndex;	
	
	float inputL;
	
	float dryWetMix = 0.5;
	
	const static int numChannels = 1;
	audio_block_t *inputQueueArray[numChannels];
};

#endif
