/* ConnectionTest.ino
 *  Tests that all encoders are connected to the proper pins and function
 *  properly as both encoders and buttons. Communicates over the serial
 *  bus to tell the user which encoder to turn or press.
 */

#include "EncoderCallback.h"
#include "ButtonCallback.h"

#define NUM_ENCODERS 6

// Encoder/button pins
#define FX1_ENCA 2
#define FX1_ENCB 1
#define FX1_BUT 3
#define FX2_ENCA 4
#define FX2_ENCB 0
#define FX2_BUT 5

#define C1B1_ENCA 41
#define C1B1_ENCB 28
#define C1B1_BUT 40
#define C1B2_ENCA 36
#define C1B2_ENCB 30
#define C1B2_BUT 35

#define C2B1_ENCA 38
#define C2B1_ENCB 29
#define C2B1_BUT 37
#define C2B2_ENCA 34
#define C2B2_ENCB 31
#define C2B2_BUT 33

#define MIX_POT 32


// Callback functions: when encoders/buttons change value
#define ENC_CALLBACK_FUNCTION &valueReceived
#define BUT_CALLBACK_FUNCTION &buttonPressed

// When a button is pressed, "bounce" can trigger multiple updates. How long after a button
// press we should wait before accepting another
#define DEBOUNCE_MS 10



void valueReceived(float newVal, float oldVal);
void buttonPressed();


// Encoder & button objects
EncoderCallback encoders[NUM_ENCODERS] = {
  EncoderCallback(String("Channel 1, Effect 1"), C1B1_ENCA, C1B1_ENCB, ENC_CALLBACK_FUNCTION),
  EncoderCallback(String("Channel 1, Effect 2"), C1B2_ENCA, C1B2_ENCB, ENC_CALLBACK_FUNCTION),
  EncoderCallback(String("Channel 1, Effect 1"), C2B1_ENCA, C2B1_ENCB, ENC_CALLBACK_FUNCTION),
  EncoderCallback(String("Channel 2, Effect 2"), C2B2_ENCA, C2B2_ENCB, ENC_CALLBACK_FUNCTION),
  EncoderCallback(String("Effect Control 1"), FX1_ENCA, FX1_ENCB, ENC_CALLBACK_FUNCTION),
  EncoderCallback(String("Effect Control 2"), FX2_ENCA, FX2_ENCB, ENC_CALLBACK_FUNCTION)
};

ButtonCallback buttons[NUM_ENCODERS] = {
  ButtonCallback(String("Channel 1, Effect 1"), C1B1_BUT, DEBOUNCE_MS, BUT_CALLBACK_FUNCTION),
  ButtonCallback(String("Channel 1, Effect 2"), C1B2_BUT, DEBOUNCE_MS, BUT_CALLBACK_FUNCTION),
  ButtonCallback(String("Channel 2, Effect 1"), C2B1_BUT, DEBOUNCE_MS, BUT_CALLBACK_FUNCTION),
  ButtonCallback(String("Channel 2, Effect 2"), C2B2_BUT, DEBOUNCE_MS, BUT_CALLBACK_FUNCTION),
  ButtonCallback(String("Effect Control 1"), FX1_BUT, DEBOUNCE_MS, BUT_CALLBACK_FUNCTION),
  ButtonCallback(String("Effect Control 2"), FX2_BUT, DEBOUNCE_MS, BUT_CALLBACK_FUNCTION)
};


// For each encoder, test turning the encoder clockwise, counterclockwise, & pressing it as a button.
enum TestType {
  EncoderInc,
  EncoderDec,
  EncoderBut
};
// Which test we're currently on
TestType mode = EncoderInc;

// The index of the encoder/button we're currently testing
int currIndex = 0;

// Are tests done
bool finished = false;


void setup() {
  Serial.begin(9600);

  Serial.println("Testing encoder " + encoders[currIndex].getName());
  Serial.println("Turn encoder clockwise click");

  mode = EncoderInc;
  currIndex = 0;
}

void loop() {
  // Look for updates on the current encoder/button
  if(!finished) {
    encoders[currIndex].encoderUpdate();
    buttons[currIndex].buttonUpdate();
  }
}

// Called when an encoder has been turned
void valueReceived(float newVal, float oldVal) {
  if(mode == EncoderInc && newVal == oldVal + 1) {
    Serial.println("Turn encoder counterclockwise one click.");
    mode = EncoderDec;
  }
  else if(mode == EncoderDec && newVal == oldVal - 1){
    Serial.println("Press encoder button");
    mode = EncoderBut;
  }
}


// Called when an button has been pressed
void buttonPressed() {
  Serial.println("Finished testing encoder " + encoders[currIndex].getName() + "\n");
    
  if(currIndex+1 < NUM_ENCODERS) {
    currIndex++;
    Serial.println("Testing encoder " + encoders[currIndex].getName());
    Serial.println("Turn encoder clockwise one click");
    mode = EncoderInc;
  }
  else {
    Serial.println("Tests complete");
    finished = true;
  }
}
