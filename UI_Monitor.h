#ifndef UI_MONITOR_H
#define UI_MONITOR_H

#include <ILI9341_t3n.h>
#include "GraphicsUtils.h"
#include "UI_Element.h"

class UI_MonitorRect : public UI_FilledRectangle {
public:
	UI_MonitorRect() : UI_FilledRectangle() {
		minY = 0;
		maxY = 0;
	}
	
	UI_MonitorRect(int minY, int maxY, int x, int y, int width, int height) : UI_FilledRectangle(x, y, width, height, 0, true) {
		this->minY = minY;
		this->maxY = maxY;
	}

	int minY;
	int maxY;
};

const int NUM_MONITOR_RECTS = 3;
const float monitorRectPercs[NUM_MONITOR_RECTS] = {0.5, 0.15, 0.35};
const uint16_t monitorRectColors[NUM_MONITOR_RECTS] = {ILI9341_GREEN, ILI9341_ORANGE, ILI9341_RED};


class UI_Monitor : public UI_Element {
public:


	UI_Monitor(int x, int y, int width, int height, int border) : UI_Element(x, y, width, height) {
		setBorder(border);

		int prevEnd = 0;
		for(int i = 0; i < NUM_MONITOR_RECTS; i++) {
			int h = height * monitorRectPercs[i];
			
			insides[i] = UI_MonitorRect(prevEnd, prevEnd + h, x + border, y + border + prevEnd, width, h);
			insides[i].setFGColor(monitorRectColors[i]);
			
			prevEnd += height * monitorRectPercs[i];
			
			Serial.print("RECT: X: ");
			Serial.print(insides[i].getX());
			Serial.print(", Y: ");
			Serial.println(insides[i].getY());
		}
		
	}

	void redraw(ILI9341_t3n* tft) {
		fillRect(tft, x, y, width + border * 2, height + border * 2, ILI9341_WHITE);
		fillRect(tft, x + border, y + border, width, height, ILI9341_BLACK);
	}

	void update(ILI9341_t3n* tft, float percentage) {
		prevFillAmount = fillAmount;
		fillAmount = percentage * height;
		
		for(int i = 0; i < NUM_MONITOR_RECTS; i++) {
			if(fillAmount <= insides[i].minY) {
				insides[i].update(tft, 0);
			}
			else if(fillAmount > insides[i].maxY) {
				insides[i].update(tft, 1);
			}
			else {
				float perc = (fillAmount - insides[i].minY)/((float) (insides[i].maxY - insides[i].minY));
				insides[i].update(tft, perc);
			}
		}
	}	
	
	
	void setBorder(int thickness) {
		border = thickness;
	}
	

private:
	int border;
	
	int fillAmount = 0;
	int prevFillAmount = 0;
	
	UI_MonitorRect insides[NUM_MONITOR_RECTS];
		
	
};

#endif