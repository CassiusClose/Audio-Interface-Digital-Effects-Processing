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

Encoder enc(28, 29);

long oldEncVal = -999;


AudioInputUSB             usbIn;

InterfaceToolMonitor      monitoring;
InterfaceToolSelector     effectSelector;

AudioOutputUSB            usbOut;
AudioOutputI2S            i2sOut;

AudioConnection           p1(usbIn, 0, monitoring, 0);
AudioConnection           p2(usbIn, 1, monitoring, 1);

AudioConnection           p3(monitoring, 0, effectSelector, 0);
AudioConnection           p4(monitoring, 1, effectSelector, 1);

AudioConnection           p5(effectSelector, 0, usbOut, 0);
AudioConnection           p6(effectSelector, 1, usbOut, 1);
AudioConnection           p7(effectSelector, 0, i2sOut, 0);
AudioConnection           p8(effectSelector, 1, i2sOut, 1);

#define DELAY_LINE_SIZE 48000
float DMAMEM delay_line_left[DELAY_LINE_SIZE];

#define TFT_DC      25
#define TFT_CS      9
#define TFT_RST    255  // 255 = unused, connect to 3.3V
#define TFT_MOSI    26
#define TFT_SCK     27
#define TFT_MISO    39
ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCK, TFT_MISO);

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
  pinMode(2, INPUT_PULLUP);

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

void loop() {

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
