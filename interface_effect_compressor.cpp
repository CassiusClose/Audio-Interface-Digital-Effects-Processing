#include <Arduino.h>
// RENAME
#include "interface_effect_compressor.h"

//RENAME CLASS
void InterfaceEffectCompressor::update(audio_block_t* blockL, audio_block_t* blockR)
{
    for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
		// AT= exp(tc/(attacktime*AUDIO_SAMPLE_RATE));
		// RT = exp(tc/(releasetime*AUDIO_SAMPLE_RATE));

		yi=blockL->data[i];
		yrect=pow(yi,2);

		if(yrect>ebuffer2){
			a = AT;
		}
		else{
			a=RT;
		}

		e2=a*ebuffer2+(1-a)*yrect;

		if (e2<0){
			e2=0;
		}

		ebuffer2=e2;
		ei=pow(e2,1/2);

		if (ei <= 0){
			d=-96;
		}
		else{
			d=20 * log10(ei);
		}
		float thresholddb=threshold;

		if(d>thresholddb){
			gain = thresholddb+(d-thresholddb)/ratiochanged-d;
		}else{
			gain=0.0;
		}

		gainlin= pow(10.0,(gain/20.0));

		blockL->data[i] = blockL->data[i] * gainlin;
		blockR->data[i] =0;
    }
}


