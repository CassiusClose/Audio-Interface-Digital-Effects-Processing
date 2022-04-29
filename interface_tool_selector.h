#ifndef interface_tool_selector_h
#define interface_tool_selector_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "AudioInterface_Effects.h"

class InterfaceToolSelector : public AudioStream
{
public:
	InterfaceToolSelector() : AudioStream(numChannels, inputQueueArray) {
		effect = &tremEffect;
	}

	virtual void update(void);
    virtual void updateCurrentEffectParam(float effectPercent){
        effect->updateParam(effectPercent);
    }
    
	void switchEffect();

private:
    const static int numChannels = 1;
	audio_block_t *inputQueueArray[numChannels];
	
	InterfaceEffectTremolo tremEffect;
	//InterfaceEffectDelay delayEffect;
	
    // Pointer to current effect
	InterfaceEffect* effect;
	
	bool trem = true;
	bool doStuff;
};

#endif
