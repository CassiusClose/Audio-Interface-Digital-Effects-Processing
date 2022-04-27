#ifndef UI_FILLED_RECTANGLE_H
#define UI_FILLED_RECTANGLE_H

#include <ILI9341_t3n.h>
#include "GraphicsUtils.h"
#include "UI_Element.h"

class UI_FilledRectangle : public UI_Element {
public:
	UI_FilledRectangle(int x = 0, int y = 0, int width = 0, int height = 0, int border = 0, bool vertical = true) : UI_Element(x, y, width, height) {
		setBorderWidth(border);
		setVertical(vertical);
	}

	void redraw(ILI9341_t3n* tft) {
		fillRect(tft, x, y, width + borderWidth * 2, height + borderWidth * 2, borderColor);
		fillRect(tft, x + borderWidth, y + borderWidth, width, height, bgColor);
	}

	void update(ILI9341_t3n* tft, float percentage) {
		if(vertical) {
			prevFillAmount = fillAmount;
			fillAmount = percentage * height;
			
			// Need to add some red
			if(fillAmount > prevFillAmount) {
				int drawHeight = fillAmount - prevFillAmount;
				fillRect(tft, x + borderWidth, y + borderWidth + prevFillAmount, width, drawHeight, fgColor);
			}
			// Remove some red
			else if(fillAmount < prevFillAmount) {
				int drawHeight = prevFillAmount - fillAmount;
				fillRect(tft, x + borderWidth, y + borderWidth + fillAmount, width, drawHeight, bgColor);
			}
		}
		else {
			prevFillAmount = fillAmount;
			fillAmount = percentage * width;
			
			if(fillAmount > prevFillAmount) {
				int drawWidth = fillAmount - prevFillAmount;
				fillRect(tft, x + borderWidth + prevFillAmount, y + borderWidth, drawWidth, height, fgColor);
			}
			else if(fillAmount < prevFillAmount) {
				int drawWidth = prevFillAmount - fillAmount;
				fillRect(tft, x + borderWidth + fillAmount, y + borderWidth, drawWidth, height, bgColor);
			}
		}
	}
	
	void setBorderWidth(int thickness) {
		borderWidth = thickness;
	}
	
	void setVertical(bool v) {
		vertical = v;
	}
	
	void setBGColor(uint16_t color) {
		bgColor = color;
	}
	
	void setFGColor(uint16_t color) {
		fgColor = color;
	}
	
	void setBorderColor(uint16_t color) {
		borderColor = color;
	}

protected:
	int borderWidth;
	bool vertical;
	
	uint16_t bgColor = ILI9341_BLACK;
	uint16_t fgColor = ILI9341_RED;
	uint16_t borderColor = ILI9341_WHITE;
	
	int fillAmount = 0;
	int prevFillAmount = 0;
	
	
};

#endif