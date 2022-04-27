#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <AudioInterface.h>
#include <AudioInterface_UI.h>


AudioInputUSB             usbIn;

InterfaceToolMonitor      monitoring;
InterfaceToolSelector     effectSelector;
InterfaceToolSelector     effectSelector1;
InterfaceToolSelector     effectSelector2;
InterfaceToolSelector     effectSelector3;
InterfaceToolSelector     effectSelector4;
InterfaceToolSelector     effectSelector5;


AudioOutputUSB            usbOut;
AudioOutputI2S            i2sOut;

AudioConnection           p1(usbIn, 0, monitoring, 0);
AudioConnection           p2(usbIn, 1, monitoring, 1);


AudioConnection           p3(monitoring, 0, effectSelector, 0);
AudioConnection           p4(monitoring, 1, effectSelector, 1);


AudioConnection           p31(effectSelector, 0, effectSelector1, 0);
AudioConnection           p41(effectSelector, 1, effectSelector1, 1);


AudioConnection           p32(effectSelector1, 0, effectSelector2, 0);
AudioConnection           p42(effectSelector1, 1, effectSelector2, 1);


AudioConnection           p33(effectSelector2, 0, effectSelector3, 0);
AudioConnection           p43(effectSelector2, 1, effectSelector3, 1);


AudioConnection           p34(effectSelector3, 0, effectSelector4, 0);
AudioConnection           p44(effectSelector3, 1, effectSelector4, 1);

AudioConnection           p35(effectSelector4, 0, effectSelector5, 0);
AudioConnection           p45(effectSelector4, 1, effectSelector5, 1);

AudioConnection           p5(effectSelector5, 0, usbOut, 0);
AudioConnection           p6(effectSelector5, 1, usbOut, 1);
AudioConnection           p7(effectSelector5, 0, i2sOut, 0);
AudioConnection           p8(effectSelector5, 1, i2sOut, 1);



#define TFT_DC      25
#define TFT_CS      9
#define TFT_RST    255  // 255 = unused, connect to 3.3V
#define TFT_MOSI    26
#define TFT_SCK     27
#define TFT_MISO    39
//ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCK, TFT_MISO);


#define UI_MONITOR_WIDTH 16
#define UI_MONITOR_HEIGHT 100
#define UI_MONITOR_BORDER 2

//UI_Monitor monitorL1(50, 75, UI_MONITOR_WIDTH, UI_MONITOR_HEIGHT, UI_MONITOR_BORDER);

float maxLevelL;
float maxLevelR;
float percentageL = 1.0;
float percentageR = 1.0;

int levelHeightL;
int levelHeightR;

int int_max = 31767;

float* w1;
float* w2;
float* w3;

void setup() {
  AudioMemory(200);
  Serial.begin(9600);
  
  //w1 = new float[(int)(AUDIO_SAMPLE_RATE)];
  //w2 = new float[(int)(AUDIO_SAMPLE_RATE)];

/*  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextSize(3);
  tft.setCursor(20, 10);
  tft.println("Audio Interface!");*/

  //monitorL1.redraw(&tft);
}

void loop() {
  Serial.println(AudioProcessorUsage());
  delay(1000);
  
  maxLevelL = monitoring.getMaxLevelL();
  maxLevelR = monitoring.getMaxLevelR();
  percentageL = maxLevelL/int_max;
  percentageR = maxLevelR/int_max;
  if(percentageL > 1.0) {
    percentageL = 1.0;
  }
  if(percentageR > 1.0) {
    percentageR = 1.0;
  }
  
  //monitorL1.update(&tft, percentageL);
}
