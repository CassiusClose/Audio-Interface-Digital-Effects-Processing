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
InterfaceEffectDelay     effect;
AudioConnection          p1(usb1, 0, effect, 0);
AudioConnection          p2(usb1, 1, effect, 1);
AudioConnection          p3(effect, 0, usb2, 0);
AudioConnection          p4(effect, 1, usb2, 1);
AudioConnection          p5(effect, 0, i2s1, 0);
AudioConnection          p6(effect, 1, i2s1, 1);

void setup() {
  // put your setup code here, to run once:
  AudioMemory(10);
}

void loop() {
  // put your main code here, to run repeatedly:

}
