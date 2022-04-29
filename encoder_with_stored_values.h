#ifndef encoder_with_stored_values_h_
#define encoder_with_stored_values_h_

#include "Arduino.h"
#include "Encoder.h"



class EncoderWithStoredValues : public Encoder
{
public:
    EncoderWithStoredValues(int A, int B, void (InterfaceToolSelector::*call)(float)):Encoder(A,B){
        callback = call;
    }
    
    int newValue;
    void encoderValueUpdate(){
      
      long newValue = read();
      if (newValue != oldValue) {
        if(newValue > 400) {
          newValue = 400;
          write(newValue);
        }else if(newValue < 0) {
          newValue = 0;
          write(newValue);
        }

        // For debugging
        if(newValue != 400) {
        oldValue = newValue;
        Serial.println(newValue/4.0);
        }

      *(newValue/4.0);
        
      }
    }
    
private:
    int oldValue;
    void (InterfaceToolSelector::*callback)(float);
};

#endif
