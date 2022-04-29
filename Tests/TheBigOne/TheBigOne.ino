#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <AudioInterface.h>
#include <AudioInterface_UI.h>
#include <ILI9341_t3n.h>
#include <ili9341_t3n_font_Arial.h>
#include <ili9341_t3n_font_ArialBold.h>
#include <Encoder.h>
#include "encoder_with_stored_values.h"

long oldEncVal = -999;

AudioInputI2S             i2sIn;
AudioInputUSB             usbIn;

InterfaceToolMonitor      monitoring;
InterfaceToolSelector     effectSelector;

AudioOutputUSB            usbOut;
AudioOutputI2S            i2sOut;

AudioMixer4               mixerLeft;
AudioMixer4               mixerRight;

AudioConnection           p1(i2sIn, 0, monitoring, 0);
AudioConnection           p2(i2sIn, 1, monitoring, 1);

AudioConnection           p3(usbIn, 0, mixerLeft, 1);
AudioConnection           p4(usbIn, 1, mixerRight, 1);

AudioConnection           p5(monitoring, 0, effectSelector, 0);
AudioConnection           p6(monitoring, 1, effectSelector, 1);

AudioConnection           p7(effectSelector, 0, usbOut, 0);
AudioConnection           p8(effectSelector, 1, usbOut, 1);

AudioConnection           p9(effectSelector, 0, mixerLeft, 0);
AudioConnection           p10(effectSelector, 1, mixerRight, 0);


AudioConnection           p11(mixerLeft, 0, i2sOut, 0);
AudioConnection           p12(mixerRight, 0, i2sOut, 1);


//#define DELAY_LINE_SIZE 48000
//float DMAMEM delay_line_left[DELAY_LINE_SIZE];

#define DISP_DC      16
#define DISP_CS      17
#define DISP_RST    255  // 255 = unused, connect to 3.3V
#define DISP_MOSI    26
#define DISP_SCK     27
#define DISP_MISO    39
ILI9341_t3n tft = ILI9341_t3n(DISP_CS, DISP_DC, DISP_RST, DISP_MOSI, DISP_SCK, DISP_MISO);

// Encoder and monitor select defines and assigns
#define FX1_ENCA 2
#define FX1_ENCB 1
#define FX1_BUT 3
#define FX2_ENCA 4
#define FX2_ENCB 0
#define FX2_BUT 5

#define C1B1_ENCA 41
#define C1B1_ENCB 28
#define C1B1_BUT 40
#define C1B2_ENCA 36
#define C1B2_ENCB 30
#define C1B2_BUT 35

#define C2B1_ENCA 38
#define C2B1_ENCB 29
#define C2B1_BUT 37
#define C2B2_ENCA 34
#define C2B2_ENCB 31
#define C2B2_BUT 33

#define MIX_POT 32

#define CALLBACK_FUNCTION &InterfaceToolSelector::updateCurrentEffectParam

// Encoder setup
EncoderWithStoredValues C1B1(C1B1_ENCA,C1B1_ENCB,CALLBACK_FUNCTION);
EncoderWithStoredValues C1B2(C1B2_ENCA,C1B2_ENCB,CALLBACK_FUNCTION);
EncoderWithStoredValues C2B1(C2B1_ENCA,C2B1_ENCB,CALLBACK_FUNCTION);
EncoderWithStoredValues C2B2(C2B2_ENCA,C2B2_ENCB,CALLBACK_FUNCTION);

EncoderWithStoredValues FX1(FX1_ENCA,FX1_ENCB,CALLBACK_FUNCTION);
EncoderWithStoredValues FX2(FX2_ENCA,FX2_ENCB,CALLBACK_FUNCTION);


#define UI_MONITOR_WIDTH 16
#define UI_MONITOR_HEIGHT 100
#define UI_MONITOR_BORDER 2

UI_Monitor monitorL1(50, 75, UI_MONITOR_WIDTH, UI_MONITOR_HEIGHT, UI_MONITOR_BORDER);
UI_ListPopup list(50, 25, 320-100, 175, String("Effects"));
//UI_FilledRectangle r1(100, 75, UI_MONITOR_WIDTH, UI_MONITOR_HEIGHT, UI_MONITOR_BORDER, true);

AudioControlSGTL5000     sgtl5000_1;     //xy=302,184

#define TEXT_X 150
#define TEXT_Y 100

float maxLevelL;
float maxLevelR;
float percentageL = 1.0;
float percentageR = 1.0;

int levelHeightL;
int levelHeightR;

int int_max = 31767;


int screenSwitchCount = 0;
bool homeScreen = false;

bool trem = false;

void setup() {
  AudioMemory(10);

  // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  Serial.begin(9600);
  Serial.println("Encoder Testing:");

  // pinMode for Direct vs computer monitoring
  pinMode(MIX_POT, INPUT_PULLUP);

  // Display setup
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextSize(3);
  tft.setCursor(20, 10);
  tft.println("Audio Interface!");


  //monitorL1.redraw(&tft);
  list.redraw(&tft);
  //r1.setup(&tft);

}

  long oldPositionFX = 50;

void loop() {

    //encodera.encoderValueUpdate;

    // Encoder updates
    C1B1.encoderValueUpdate;
    C1B2.encoderValueUpdate;
    C2B1.encoderValueUpdate;
    C2B2.encoderValueUpdate;
    
    FX1.encoderValueUpdate;
    FX2.encoderValueUpdate;
  
  /*screenSwitchCount++;
  if(screenSwitchCount == 50) {
    screenSwitchCount = 0;
    tft.fillScreen(ILI9341_BLACK);
    if(homeScreen) {
      Serial.println("Drawing list");
      list.redraw(&tft);
    }
    else {
    Serial.println("Drawing monitor");
      monitorL1.redraw(&tft);
    }
    homeScreen = !homeScreen;
  }*/

  if(homeScreen) {
    
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
  
    monitorL1.update(&tft, percentageL);
  }
  else {
    
  }
  //r1.update(&tft, percentageL);

  
  delay(30);
  
  /*long encVal = enc.read()/4.0;
  if(encVal != oldEncVal) {
    oldEncVal = encVal;

    tft.fillRect(TEXT_X, TEXT_Y, 150, 200, ILI9341_BLACK);


    if(trem)
      tft.setFont( Arial_20 );
    else
      tft.setFont( Arial_20_Bold );
    tft.setCursor(TEXT_X, TEXT_Y);
    tft.print("Bypass");

    
    tft.setTextColor(ILI9341_WHITE);
    if(trem)
      tft.setFont( Arial_20_Bold );
    else
      tft.setFont( Arial_20);
    tft.setCursor(TEXT_X, TEXT_Y+40);
    tft.print("Tremolo");

    effectSelector.switchEffect();

    trem = !trem;
  }*/
}
