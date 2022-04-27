#ifndef TREMOLO_H
#define TREMOLO_H

#include "effect.h"
#include <cmath>

class Tremolo : public Effect {
public:
    Tremolo(int sr) : Effect(sr) {
        wavetable = new float[sr];
        for(int i = 0; i < sampleRate; i++) {
            wavetable[i] = sin(2 * M_PI * i / sampleRate);
        }
    }

    ~Tremolo() {
        delete wavetable;
    }

    void callback(int* buf, int numSamples) {
        for(int i = 0; i < numSamples; i++) {
            buf[i] *= wavetable[wtIndex];
            buf[i] *= wavetable[wtIndex];
            wtIndex++;
            if(wtIndex == sampleRate)
                wtIndex = 0;
        }
    }

    float* wavetable;
	int wtIndex;

};

#endif
