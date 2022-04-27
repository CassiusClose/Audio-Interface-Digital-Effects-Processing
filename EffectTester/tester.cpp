#include <sndfile.h>
#include <iostream>

#include "effect.h"

#define BUFSIZE 64

int main(int argc, char* argv[]) {

    if(argc != 2) {
        std::cout << "Usage: " << argv[0] << " filename" << std::endl;
        return -1;
    }

    SF_INFO info;
    info.format = 0;
    SNDFILE* readfile = sf_open(argv[1], SFM_READ, &info);
    if(readfile == NULL) {
        std::cout << "Error reading file " << argv[1] << std::endl;
        return -1;
    }

    if(info.channels != 1) {
        std::cout << "Error: Only supports 1 channel of audio" << std::endl;
        sf_close(readfile);
        return -1;
    }


    SNDFILE* writefile = sf_open("out.wav", SFM_WRITE, &info);
    if(writefile == NULL) {
        std::cout << "Error opening write file " << argv[1] << std::endl;
        sf_close(readfile);
        return -1;
    }

    Effect* effect;
    effect = new Delay(info.samplerate);


    int buffer[BUFSIZE];
    sf_count_t numSamples = 0;
    do {
        numSamples = sf_readf_int(readfile, buffer, BUFSIZE);

        effect->callback(buffer, BUFSIZE);

        sf_writef_int(writefile, buffer, numSamples);

    } while(numSamples != 0);


    delete effect;

    sf_close(readfile);
    sf_close(writefile);

    return 0;
}


