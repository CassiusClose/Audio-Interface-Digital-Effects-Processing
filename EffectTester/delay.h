#ifndef DELAY_H 
#define DELAY_H

#include "effect.h"

#define DELAY_LINE_LEN 1

class Delay : public Effect {
public:
    Delay(int sr) : Effect(sr) {
        delayLine = new float[sr * DELAY_LINE_LEN];
        delayLineIndex = 0;
    }

    ~Delay() {
        delete delayLine;
    }

    void callback(int* buf, int numSamples) {
        for(int i = 0; i < numSamples; i++) {
            input = buf[i];
            
            buf[i] = buf[i] * (1 - dryWetMix) + dryWetMix * delayLine[delayLineIndex];
            
            delayLine[delayLineIndex] = input + delayLine[delayLineIndex] * feedback;
            
            delayLineIndex++;
            if(delayLineIndex >= sampleRate * DELAY_LINE_LEN)
                delayLineIndex = 0;
        }
    }

	float* delayLine;
	int delayLineIndex;	

    int input;

    float dryWetMix = 0.5;
    float feedback = 0.2;

};

#endif
