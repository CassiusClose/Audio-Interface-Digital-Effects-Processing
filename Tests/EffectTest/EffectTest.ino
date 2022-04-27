#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <AudioInterface.h>

// GUItool: begin automatically generated code
AudioInputUSB            usb1;           //xy=330,276
AudioOutputUSB           usb2;           //xy=498,264
AudioOutputI2S           i2s1;           //xy=538,332
InterfaceToolSelector    effectSelector;
AudioConnection          p1(usb1, 0, effectSelector, 0);
AudioConnection          p2(usb1, 1, effectSelector, 1);
AudioConnection          p3(effectSelector, 0, usb2, 0);
AudioConnection          p4(effectSelector, 1, usb2, 1);
AudioConnection          p5(effectSelector, 0, i2s1, 0);
AudioConnection          p6(effectSelector, 1, i2s1, 1);

void setup() {
	
	  // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);
  
  // put your setup code here, to run once:
  AudioMemory(10);
}

void loop() {
  // put your main code here, to run repeatedly:

}
