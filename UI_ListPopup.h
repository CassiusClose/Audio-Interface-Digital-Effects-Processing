#ifndef UI_LIST_POPUP_H
#define UI_LIST_POPUP_H

#include <Arduino.h>
#include <ILI9341_t3n.h>
#include <ili9341_t3n_font_Arial.h>
#include <ili9341_t3n_font_ArialBold.h>
#include "GraphicsUtils.h"
#include "UI_Element.h"
#include <string>
#include <vector>


#define LIST_ITEM_X_MARGIN 5


const int NUM_ITEMS = 4;
const String itemNames[NUM_ITEMS] = { String("Hello"), String("Long list item name"), String("Hell yeah"), String("Ben Lapidus") };

class UI_ListItem : public UI_Element {
public:
	UI_ListItem(String text, uint16_t color, int x, int y, int w, int h) : UI_Element(x, y, w, h) {
		this->text = text;
		this->color = color;
	}
	
	void redraw(ILI9341_t3n* tft) {
		Serial.println("Drawing");
		fillRect(tft, x, y, width, height, color);
		
		int textY = y + (height/2.0) + (font.cap_height/2.0);
        if(selected) {
		    drawText(tft, text, x + xMargin, textY, fontSelected, ILI9341_WHITE);
        }
        else {
		    drawText(tft, text, x + xMargin, textY, font, ILI9341_WHITE);
        }
	}

    void setSelected(bool sel) {
        selected = sel;
    }
	
private:
	String text;
	uint16_t color;
	ILI9341_t3_font_t font = Arial_16;
    ILI9341_t3_font_t fontSelected = Arial_16_Bold;
    int xMargin = LIST_ITEM_X_MARGIN;
    bool selected = false;
};

class UI_ListPopup : public UI_Element {
public:
	UI_ListPopup(int x, int y, int width, int height, String title) : UI_Element(x, y, width, height) {
		this->title = title;
		
		int itemY = y + height - 16 - 10;
		bool red = true;
        int itemHeight = 30;
		for(int i = 0; i < NUM_ITEMS; i++) {
			itemY -= itemHeight;
			Serial.print("Item: ");
			Serial.println(itemY);
			if(red) {
				items.push_back(UI_ListItem(itemNames[i], ILI9341_RED, x, itemY, width, itemHeight)); 
			}
			else {
				items.push_back(UI_ListItem(itemNames[i], ILI9341_GREEN, x, itemY, width, itemHeight));
			}
			red = !red;
		}

        items[0].setSelected(true);
	}
	
	void redraw(ILI9341_t3n* tft) {
		//fillRect(tft, x, y, width, height, ILI9341_GREEN);
		drawText(tft, title, x, y + height, Arial_16, ILI9341_WHITE);
		
		Serial.print("NUM: ");
		Serial.println(NUM_ITEMS);
		for(int i = 0; i < 4; i++) {
			Serial.println(i);
			items[i].redraw(tft);
		}
	}
	
	
private:
	String title;
	std::vector<UI_ListItem> items;
};

#endif
