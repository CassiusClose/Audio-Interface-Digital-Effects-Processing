#ifndef interface_effect_template_h_
#define interface_effect_template_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "InterfaceEffect.h"

class InterfaceEffectTemplate : public InterfaceEffect
{
public:
	InterfaceEffectTemplate() : InterfaceEffect(true, false) {}

	virtual void update(audio_block_t* blockL, audio_block_t* blockR);

private:
};

#endif
