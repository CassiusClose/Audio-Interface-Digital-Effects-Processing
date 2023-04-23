#ifndef ENCODER_CALLBACK_H
#define ENCODER_CALLBACK_H

#include "Arduino.h"
#include "Encoder.h"

/*
 * A modified encoder class that calls a callback function when the encoder has been turned.
 * Users must call encoderUpdate() to check for change. Keeps the encoder values in a range
 * between 0% and 100%, and provides them as floats (0-1) to the user.
 */
class EncoderCallback : public Encoder
{
public:
    /* Constructor
     * call: A pointer to the callback function
     * mult: How many percent the encoder should change by each click.
     */
    EncoderCallback(String name, int A, int B, void (*call)(float, float), float mult = 1) : Encoder(A,B){
        callback = call;
        oldValue = read();
        this->name = name;
        this->mult = mult;
        upperLimit = 100*4/mult;
    }
    
    /* Call this every loop. This will check for encoder turns & call the callback function
     * if there were any.
     */
    void encoderUpdate(){
      
        newValue = read();
        // Our encoders move by 4 for each click, and have some bounce between each click. So in going from 0 to 3 (one click),
        // it might read 0, 1, 0, 1, 2, 1, 2, 3. This makes sure the encoder has reached its destination (all 4 positions) before
        // it considers the value changed.
        if((newValue > oldValue && (newValue-oldValue) % 4 == 0) || (newValue < oldValue && (oldValue-newValue) % 4 == 0)) {
            if(newValue > upperLimit) {
                newValue = upperLimit;
                write(newValue);
            }
            else if(newValue < 0) {
                newValue = 0;
                write(newValue);
            
            }

            // If something has changed, call the callback. Convert from raw encoder value to
            // percent between 0 & 1.
            if(callback != NULL && newValue != oldValue)
                callback(newValue*mult/400.0, oldValue*mult/400.0);
            
            oldValue = newValue;
        }
    }
    
    String getName() { return name; }
    
private:
    long newValue;
    long oldValue;
    
    // Callback function, called when the encoder changes value. The first argument is the new encoder value,
    // the second argument is the old encoder value.
    void (*callback)(float, float);
    
    float mult;
    int upperLimit;
    String name;
};

#endif
