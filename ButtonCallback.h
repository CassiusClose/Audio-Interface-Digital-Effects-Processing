#ifndef BUTTON_CALLBACK_H
#define BUTTON_CALLBACK_H

#include "Bounce.h"

/*
 * A modified button class that calls a callback function when the button has been pressed.
 * Users must call buttonUpdate() to check for presses.
 */
class ButtonCallback : public Bounce {
public:
	/* The 4th argument is a pointer to a callback function */
	ButtonCallback(String name, int pin, int debounce, void (*call)()) : Bounce(pin, debounce) {
		pinMode(pin, INPUT_PULLUP);
		callback = call;
		this->name = name;
	}
	
	/* Call this every loop. This will check for button presses & call the callback function
	 * if there were any.
	 */
	void buttonUpdate() {
		if(update()) {
			// Don't accept new presses until the user releases the button after the first click.
			if(!currentlyPressed && fallingEdge()) {
				currentlyPressed = true;	
				callback();
			}
			// The user has released the button
			else if(risingEdge()) {
				currentlyPressed = false;
			}
		}
	}
	
	String getName() { return name; }
	
private:
	String name;
	
	// Is the button currently pressed down
	bool currentlyPressed = false;
	
	// The callback function that will be called when the button is pressed.
    void (*callback)();
};

#endif