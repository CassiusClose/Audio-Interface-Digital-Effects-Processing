#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include <ILI9341_t3n.h>

class UI_Element {
public:
	UI_Element(int x = 0, int y = 0, int width = 0, int height = 0) {
		setLocation(x, y);
		setSize(width, height);
	}
	
	virtual void redraw(ILI9341_t3n* tft) {}
		
	void setLocation(int x, int y) {
		this->x = x;
		this->y = y;
	}
	
	int getX() {
		return x;
	}
	
	int getY() {
		return y;
	}
	
	void setSize(int w, int h) {
		width = w;
		height = h;
	}
	
	int getWidth() {
		return width;
	}
	
	int getHeight() {
		return height;
	}

protected:
	int x;
	int y;
	int width;
	int height;
};

#endif
