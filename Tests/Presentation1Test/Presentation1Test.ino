#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <AudioInterface.h>
#include <ILI9341_t3n.h>
#include <ili9341_t3n_font_Arial.h>
#include <ili9341_t3n_font_ArialBold.h>
#include <Encoder.h>

Encoder enc(28, 29);

long oldEncVal = -999;


// GUItool: begin automatically generated code
AudioInputUSB             usbIn;           //xy=330,276

InterfaceToolMonitor      monitoring;
InterfaceToolSelector     effectSelector;

AudioOutputUSB            usbOut;           //xy=498,264
AudioOutputI2S            i2sOut;           //xy=538,332

AudioConnection           p1(usbIn, 0, monitoring, 0);
AudioConnection           p2(usbIn, 1, monitoring, 1);

AudioConnection           p3(monitoring, 0, effectSelector, 0);
AudioConnection           p4(monitoring, 1, effectSelector, 1);
AudioConnection           p5(effectSelector, 0, usbOut, 0);
AudioConnection           p6(effectSelector, 1, usbOut, 1);
AudioConnection           p7(effectSelector, 0, i2sOut, 0);
AudioConnection           p8(effectSelector, 1, i2sOut, 1);

#define TFT_DC      32
#define TFT_CS      37
#define TFT_RST    255  // 255 = unused, connect to 3.3V
#define TFT_MOSI    26
#define TFT_SCK     27
#define TFT_MISO    39
ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCK, TFT_MISO);

AudioControlSGTL5000     sgtl5000_1;     //xy=302,184


#define MONITOR_X 50
#define MONITOR_Y 75

#define MONITOR_WIDTH 15
#define MONITOR_HEIGHT 100
#define MONITOR_MARGIN 2


#define TEXT_X 150
#define TEXT_Y 100

float maxLevelL;
float maxLevelR;
float percentageL = 1.0;
float percentageR = 1.0;

int levelHeightL;
int levelHeightR;

int int_max = 31767;

bool trem = false;

void setup() {
  AudioMemory(10);

  // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextSize(3);
  tft.setCursor(20, 10);
  tft.println("Audio Interface!");

  tft.fillRect(MONITOR_X, MONITOR_Y, MONITOR_WIDTH*2 + MONITOR_MARGIN*2, MONITOR_HEIGHT + MONITOR_MARGIN*2, ILI9341_WHITE);
  tft.fillRect(MONITOR_X + MONITOR_MARGIN, MONITOR_Y + MONITOR_MARGIN, MONITOR_WIDTH*2, MONITOR_HEIGHT, ILI9341_BLACK);
}

void loop() {

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
  
  tft.fillRect(MONITOR_X + MONITOR_MARGIN, MONITOR_Y + MONITOR_MARGIN, MONITOR_WIDTH*2, MONITOR_HEIGHT, ILI9341_BLACK);

  levelHeightL = MONITOR_HEIGHT * percentageL;
  levelHeightR = MONITOR_HEIGHT * percentageR;

  int yL = MONITOR_Y + MONITOR_MARGIN + (MONITOR_HEIGHT - levelHeightL);
  tft.fillRect(MONITOR_X + MONITOR_MARGIN, yL, MONITOR_WIDTH, levelHeightL, ILI9341_RED);

  int yR = MONITOR_Y + MONITOR_MARGIN + (MONITOR_HEIGHT - levelHeightR);
  tft.fillRect(MONITOR_X + MONITOR_MARGIN + MONITOR_WIDTH, yR, MONITOR_WIDTH, levelHeightR, ILI9341_RED);

  delay(30);
  
  long encVal = enc.read()/4.0;
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
  }
}
