/*#include <Arduino.h>
#include <Adafruit_MCP23X17.h>
#include "Rotary.h"
#include <Wire.h>

int result;

Adafruit_MCP23X17 mcp;

Rotary r = Rotary(&mcp, 5, 6);

void setup() {
  Serial.begin(9600);
  if(!mcp.begin_I2C()) {
    Serial.println("Error initializing MCP connection.");
    while(1);
  }

  mcp.pinMode(5, INPUT_PULLUP);
  mcp.pinMode(6, INPUT_PULLUP);

  /*
  Wire.beginTransmission(0x20); //23017 address
  Wire.write(0x0C); // set MCP23017 memory pointer to GPIOA address
  Wire.write(0xFF); //enable pullup???
  Wire.endTransmission();
*
  
  Serial.println("MCP Done");
  r.begin();
  Serial.println("Rotary Done");
}

void loop() {
  /*unsigned char result1 = mcp.digitalRead(5);
  unsigned char result2 = mcp.digitalRead(6);
  Serial.print("Pins: ");
  Serial.print(result1);
  Serial.print(", ");
  Serial.print(result2);
  Serial.println();*
  
  
  
  result = r.process();
  if (result) {
    Serial.println(result == DIR_CW ? "Right" : "Left");
  } 
}
*/



#if 0
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MCP23X17.h>
#include "Rotary.h"
#include "RotaryEncOverMCP.h"

/* Our I2C MCP23017 GPIO expanders */
Adafruit_MCP23X17 mcp;

/* function prototypes */
void RotaryEncoderChanged(bool clockwise, int id);

/* Array of all rotary encoders and their pins */
RotaryEncOverMCP rotaryEncoders[] = {
        // outputA,B on GPA7,GPA6, register with callback and ID=1
        RotaryEncOverMCP(&mcp, 6, 5, &RotaryEncoderChanged, 1)
};
constexpr int numEncoders = (int)(sizeof(rotaryEncoders) / sizeof(*rotaryEncoders));

void RotaryEncoderChanged(bool clockwise, int id) {
    Serial.println("Encoder " + String(id) + ": "
            + (clockwise ? String("clockwise") : String("counter-clock-wise")));
}

void setup(){
    Serial.begin(115200);
    Serial.println("MCP23007 Polling Test");

    if(!mcp.begin_I2C()) {// use default address 0
      Serial.println("Error.");
      while(1) {}
    }

    //Initialize input encoders (pin mode, interrupt)
    for(int i=0; i < numEncoders; i++) {
        rotaryEncoders[i].init();
    }
}

void pollAll() {
    uint16_t gpioAB = mcp.readGPIOAB();
    Serial.println(gpioAB);
    for (int i=0; i < numEncoders; i++) {
            //only feed this in the encoder if this
            //is coming from the correct MCP
        if(rotaryEncoders[i].getMCP() == &mcp) {
            rotaryEncoders[i].feedInput(gpioAB);
        }
    }
}

void loop() {
    pollAll();
}
#endif



#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include "Rotary.h"
#include "RotaryEncOverMCP.h"

#if defined(ESP32) || defined(ESP8266)
#define INTERRUPT_FUNC_ATTRIB IRAM_ATTR
#else
#define INTERRUPT_FUNC_ATTRIB  
#endif

/* Our I2C MCP23017 GPIO expanders */
Adafruit_MCP23017 mcp;

/* the INT pin of the MCP can only be connected to
 * an interrupt capable pin on the Arduino, either
 * D3 or D2.
 * */
byte arduinoIntPin = 26;

/* variable to indicate that an interrupt has occured */
volatile boolean awakenByInterrupt = false;

/* function prototypes */
void intCallBack();
void cleanInterrupts();
void handleInterrupt();
void RotaryEncoderChanged(bool clockwise, int id);

/* Array of all rotary encoders and their pins */
RotaryEncOverMCP rotaryEncoders[] = {
    // outputA,B on GPB7,GPB6, register with callback and ID=1 (GPB0=7 .. GPB7=15)
    RotaryEncOverMCP(&mcp, 6, 5, &RotaryEncoderChanged, 1),
};
constexpr int numEncoders = (int)(sizeof(rotaryEncoders) / sizeof(*rotaryEncoders));

void RotaryEncoderChanged(bool clockwise, int id) {
    Serial.println("Encoder " + String(id) + ": "
            + (clockwise ? String("clockwise") : String("counter-clock-wise")));
}

void setup(){

    Serial.begin(115200);
    Serial.println("MCP23007 Interrupt Test");

    pinMode(arduinoIntPin,INPUT);

    mcp.begin();      // use default address 0
    mcp.readINTCAPAB(); //read this so that the interrupt is cleared

    //initialize all rotary encoders

    //Setup interrupts, OR INTA, INTB together on both ports.
    //thus we will receive an interrupt if something happened on
    //port A or B with only a single INT connection.
    mcp.setupInterrupts(true,false,LOW);

    //Initialize input encoders (pin mode, interrupt)
    for(int i=0; i < numEncoders; i++) {
        rotaryEncoders[i].init();
    }

    attachInterrupt(digitalPinToInterrupt(arduinoIntPin), intCallBack, FALLING);
}

// The int handler will just signal that the int has happened
// we will do the work from the main loop.
void INTERRUPT_FUNC_ATTRIB intCallBack() {
    awakenByInterrupt=true;
    //Serial.println("INT");
}

void checkInterrupt() {
    if(awakenByInterrupt) {
        // disable interrupts while handling them.
        detachInterrupt(digitalPinToInterrupt(arduinoIntPin));
        //Serial.println("Detached");
        handleInterrupt();
        attachInterrupt(digitalPinToInterrupt(arduinoIntPin),intCallBack,FALLING);
        
        /* What I think was happening was that another interrupt was coming after the
         * interrupt was cleared in handleInterrupt(), but before the interrupt handler
         * was reattached. So the interrupt flag would be set, but it would never get
         * handled, and any more interrupts would be ignored since the flag was already
         * set. Clearing the interrupt flag after the handler is reattached seems to fix
         * this issue.
         */
        
        mcp.readINTCAPAB();
        //Serial.println("Reattached");
    }
}

void handleInterrupt(){
    //Read the entire state when the interrupt occurred

    //An interrupt occurred on some MCP object.
    //since all of them are ORed together, we don't
    //know exactly which one has fired.
    //just read all of them, pre-emptively.

    uint16_t gpioAB = mcp.readINTCAPAB();
    // we need to read GPIOAB to clear the interrupt actually.
    volatile uint16_t dummy = mcp.readGPIOAB();
    for (int i=0; i < numEncoders; i++) {
        //only feed this in the encoder if this
        //is coming from the correct MCP
        if(rotaryEncoders[i].getMCP() == &mcp)
            rotaryEncoders[i].feedInput(gpioAB);
    }

    cleanInterrupts();
}

// handy for interrupts triggered by buttons
// normally signal a few due to bouncing issues
void cleanInterrupts(){
#ifdef __AVR__
    EIFR=0x01;
#endif
    awakenByInterrupt=false;
}

void loop() {
    //Check if an interrupt has occurred and act on it
    checkInterrupt();
}
