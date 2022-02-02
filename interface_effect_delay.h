#ifndef interface_effect_delay_h_
#define interface_effect_delay_h_

#include <math.h>
#include "Arduino.h"
#include "AudioStream.h"

#define DELAY_LINE_LEN 1

class InterfaceEffectDelay : public AudioStream
{
public:
	InterfaceEffectDelay() : AudioStream(1, inputQueueArray) {
        memset(delayLine, 0, sizeof(delayLine));
		delayLineIndex = 0;
    }

	virtual void update(void);

private:
	float delayLine[(int) (AUDIO_SAMPLE_RATE * DELAY_LINE_LEN)];
	int delayLineIndex;	
	
	float input;
	
	float dryWetMix = 0.5;
	
	audio_block_t *inputQueueArray[1];
};

#endif
