#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <AudioInterface.h>
#include "ILI9341_t3.h"
#include <Encoder.h>

Encoder enc(3,4);

long oldEncVal = -999;


// GUItool: begin automatically generated code
AudioInputUSB            usb1;           //xy=330,276
AudioOutputUSB           usb2;           //xy=498,264
AudioOutputI2S           i2s1;           //xy=538,332
InterfaceToolMonitor     monitoring;
AudioConnection          p1(usb1, 0, monitoring, 0);
AudioConnection          p3(monitoring, 0, usb2, 0);
AudioConnection          p5(monitoring, 0, i2s1, 0);

#define TFT_DC  9
#define TFT_CS 10

ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

#define MONITOR_X 20
#define MONITOR_Y 50

#define MONITOR_WIDTH 15
#define MONITOR_HEIGHT 100
#define MONITOR_MARGIN 2

float percentage = 1.0;
int levelHeight;

int int_max = 31767;

void setup() {
  // put your setup code here, to run once:
  AudioMemory(10);

  Serial.begin(9600);
  while(!Serial) {}
  pinMode(2, INPUT_PULLUP);

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextSize(3);
  tft.println("Audio Interface!");

  tft.fillRect(MONITOR_X, MONITOR_Y, MONITOR_WIDTH + MONITOR_MARGIN*2, MONITOR_HEIGHT + MONITOR_MARGIN*2, ILI9341_WHITE);
  tft.fillRect(MONITOR_X + MONITOR_MARGIN, MONITOR_Y + MONITOR_MARGIN, MONITOR_WIDTH, MONITOR_HEIGHT, ILI9341_BLACK);
}

void loop() {

  float maxLevel = monitoring.getMaxLevel();
  Serial.println(maxLevel);
  percentage = maxLevel/int_max;
  Serial.println(percentage);
  Serial.println();
  
  tft.fillRect(MONITOR_X + MONITOR_MARGIN, MONITOR_Y + MONITOR_MARGIN, MONITOR_WIDTH, MONITOR_HEIGHT, ILI9341_BLACK);

  levelHeight = MONITOR_HEIGHT * percentage;

  int y = MONITOR_Y + MONITOR_MARGIN + (MONITOR_HEIGHT - levelHeight);
  tft.fillRect(MONITOR_X + MONITOR_MARGIN, y, MONITOR_WIDTH, levelHeight, ILI9341_RED);

  delay(20);
  
  long encVal = enc.read()/4.0;
  if(encVal != oldEncVal) {
    tft.fillRect(100, 100, 80, 80, ILI9341_BLACK);
    tft.setCursor(100, 100);
    tft.setTextColor(ILI9341_WHITE);
    tft.print(encVal);
    oldEncVal = encVal;
  }
}
