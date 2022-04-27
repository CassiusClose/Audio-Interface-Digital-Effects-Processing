#ifndef GRAPHICS_UTILS_H
#define GRAPHICS_UTILS_H

#include <Arduino.h>
#include <ILI9341_t3n.h>

void fillRect(ILI9341_t3n* tft, int x, int y, int width, int height, uint16_t color) {
	tft->fillRect(x, ILI9341_TFTWIDTH - y - height, width, height, color);
}

void drawText(ILI9341_t3n* tft, String text, int x, int y, ILI9341_t3_font_t font, uint16_t color) {
	tft->setTextColor(color);
	tft->setFont(font);
	tft->drawString(text, x, ILI9341_TFTWIDTH - y);
}

void drawText(ILI9341_t3n* tft, String text, int x, int y, int textSize, uint16_t color) {
	tft->setTextColor(color);
	tft->setTextSize(textSize);
	tft->setFontAdafruit();
	tft->drawString(text, x, ILI9341_TFTWIDTH - y);
}


#endif