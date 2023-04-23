#ifndef interface_effect_compressor_h_
#define interface_effect_compressor_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "InterfaceEffect.h"

/* 
 * A compressor audio effect.
 */
class InterfaceEffectCompressor : public InterfaceEffect
{
public:
	// Arguments: stereo (bool), readonly (bool)
	InterfaceEffectCompressor() : InterfaceEffect(false, false) {}


private:
	virtual void processAudio(audio_block_t* block);
    
    float threshold=0.0;
    float attacktime=0.02;
    float releasetime=0.2;
    float tc=log(0.368);
    float ratio=4;
    float ebuffer2 = 0;
    float a;
    float e2;
    float ei;

    float d;
    float gain;
    float gainlin;
    float ratiochanged=4.0;

    float yi;
    float yrect;
    float AT= exp(tc/(attacktime*AUDIO_SAMPLE_RATE));;
    float RT= exp(tc/(releasetime*AUDIO_SAMPLE_RATE));

};

#endif
