#include <Arduino.h>
#include "interface_tool_selector.h"
#include "AudioInterface_Effects.h"

void InterfaceToolSelector::update(void)
{
	audio_block_t *blockL;

	if(effect->isReadOnly())
		blockL = receiveReadOnly(0);
	else
		blockL = receiveWritable(0);

    if(!blockL)
        return;
	
	
	/*audio_block_t *blockR;

	if(effect->isReadOnly())
		blockR = receiveReadOnly(1);
	else
		blockR = receiveWritable(1);
	
    if(!blockR) {
        release(blockL);
        return;
    }*/

	if(trem)
		effect->update(blockL, NULL);

    transmit(blockL, 0);
    //transmit(blockR, 1);
    release(blockL);
    //release(blockR);
}

void InterfaceToolSelector::switchEffect(void) {
	if(trem) {
		//effect = &delayEffect;
	}
	else {
		effect = &tremEffect;
	}
	
	trem = !trem;	
}
