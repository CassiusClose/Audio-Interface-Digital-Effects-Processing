#ifndef EFFECT_H
#define EFFECT_H

class Effect {
public:
    Effect(int sampleRate) : sampleRate{sampleRate} {}
    virtual ~Effect() {}

    virtual void callback(int* buf, int numSamples) = 0;

    int sampleRate;
};


#include "tremolo.h"
#include "delay.h"

#endif
