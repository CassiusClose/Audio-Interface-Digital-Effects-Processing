#ifndef INTERFACE_EFFECT_H
#define INTERFACE_EFFECT_H

#include "Arduino.h"
#include "AudioStream.h"


class InterfaceEffect {
public:
	
	InterfaceEffect(bool stereo, bool readOnly) {
		this->stereo = stereo;
		this->readOnly = readOnly;
	}
	
	virtual void update(audio_block_t *blockL, audio_block_t *blockR) {
		
	}
    
    virtual void updateParam(float effectAmount){
        
    }
	
	bool isStereo() { return stereo; }
	bool isReadOnly() { return readOnly; }
	
private:
	bool stereo;
	bool readOnly;
};


#endif
