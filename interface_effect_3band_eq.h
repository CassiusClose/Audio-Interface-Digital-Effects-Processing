#ifndef interface_effect_3band_eq_h_
#define interface_effect_3band_eq_h_

#include <math.h>
#include "Arduino.h"
#include "AudioStream.h"
#include "InterfaceEffect.h"

class lp_biquad{
	private:

		float x1;
		float x2;
		float y1;
		float y2;

	public:
	float b0;
	float b1;
	float b2;
	float a0;
	float a1;
	float a2;
	lp_biquad(){
		reset();
	}
	void reset(){
		x1=0;
		x2=0;
		y1=0;
		y2=0;

	}
	void set(float f0, float Q){
		float w0 =2*PI*f0/AUDIO_SAMPLE_RATE;
		float alpha = sin(w0)/(2*Q);

		a0 = 1.0 + alpha;
		a1 = -2.0 * cos(w0);
		a2 = 1.0 - alpha;
		b0 = (1.0 - cos(w0)) / 2.0;
		b1 = 1.0 - cos(w0);
		b2 = (1.0 - cos(w0)) / 2.0;

	}
	float doBiquad(float xn){

		float output = (b0/a0)*xn+(b1/a0)*x1+(b2/a0)*x2-(a1/a0)*y1-(a2/a0)*y2;
		y2 = y1;
		y1 = output;
		x2 = x1;
		x1 = xn;
		return output;

	}


};

class hp_biquad{
	private:

		float x1;
		float x2;
		float y1;
		float y2;

	public:
	float b0;
	float b1;
	float b2;
	float a0;
	float a1;
	float a2;
	hp_biquad(){
		reset();
	}
	void reset(){
		x1=0;
		x2=0;
		y1=0;
		y2=0;

	}
	void set(float f0, float Q){
		float w0 =2*PI*f0/AUDIO_SAMPLE_RATE;
		float alpha = sin(w0)/(2*Q);

		a0 = 1.0 + alpha;
		a1 = -2.0 * cos(w0);
		a2 = 1.0 - alpha;
		b0 = (1.0 + cos(w0)) / 2.0;
		b1 = -(1.0 + cos(w0));
		b2 = (1.0 + cos(w0)) / 2.0;

	}
	float doBiquad(float xn){

		float output = (b0/a0)*xn+(b1/a0)*x1+(b2/a0)*x2-(a1/a0)*y1-(a2/a0)*y2;
		y2 = y1;
		y1 = output;
		x2 = x1;
		x1 = xn;
		return output;

	}


};

class InterfaceEffectEQ : public InterfaceEffect
{
public:
	// Arguments: stereo (bool), readonly (bool)
	InterfaceEffectEQ() : InterfaceEffect(true, false) {}

	virtual void update(audio_block_t* blockL, audio_block_t* blockR);



private:
	
	float input;
    float low;
    float high;
    float mid;

    float lowcoeff=0;
    float midcoeff=1;
    float highcoeff=0;
	
	float dryWetMix = 1;
	lp_biquad lowpass;
	hp_biquad highpass;
	
	
};



#endif