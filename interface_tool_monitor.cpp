#include <Arduino.h>
#include "interface_tool_monitor.h"

void InterfaceToolMonitor::update(void)
{
	audio_block_t *blockL = receiveReadOnly(0);

    if(!blockL)
        return;
	
	audio_block_t *blockR = receiveReadOnly(1);

	if(!blockR) {
		release(blockL);
		return;
	}
	
    for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
		abs = blockL->data[i];
		if(abs < 0)
			abs *= -1;
		
		if(abs > maxLevelL)
			maxLevelL = abs;
		
		
		abs = blockR->data[i];
		if(abs < 0)
			abs *= -1;
		
		if(abs > maxLevelR)
			maxLevelR = abs;
    }
	
	transmit(blockL, 0);
	transmit(blockR, 1);
    release(blockL);
	release(blockR);
}

int InterfaceToolMonitor::getMaxLevelL() {
	int m = maxLevelL;
	maxLevelL = 0;
	return m;
}

int InterfaceToolMonitor::getMaxLevelR() {
	int m = maxLevelR;
	maxLevelR = 0;
	return m;
}


