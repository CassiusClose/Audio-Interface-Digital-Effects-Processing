#ifndef interface_effect_template_h_
#define interface_effect_template_h_

#include "Arduino.h"
#include "AudioStream.h"

class InterfaceEffectTemplate : public AudioStream
{
public:
	InterfaceEffectTemplate() : AudioStream(numChannels, inputQueueArray) {
    }

	virtual void update(void);

private:
    const static int numChannels = 2;
	audio_block_t *inputQueueArray[numChannels];
};

#endif
