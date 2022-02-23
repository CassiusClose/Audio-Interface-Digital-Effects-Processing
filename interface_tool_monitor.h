#ifndef interface_tool_monitor_h_
#define interface_tool_monitor_h_

#include "Arduino.h"
#include "AudioStream.h"

class InterfaceToolMonitor : public AudioStream
{
public:
	InterfaceToolMonitor() : AudioStream(numChannels, inputQueueArray) {
    }

	virtual void update(void);
	
	int getMaxLevelL();
	int getMaxLevelR();

private:
    const static int numChannels = 2;
	audio_block_t *inputQueueArray[numChannels];
	
	int maxLevelL = 0;
	int maxLevelR = 0;
	int abs;
};

#endif
