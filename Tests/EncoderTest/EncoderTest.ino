#include <Encoder.h>

Encoder enc(3,4);

long oldEncVal = -999;

void setup() {
  Serial.begin(9600);
  while(!Serial) {}
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  long encVal = enc.read();
  if(encVal != oldEncVal) {
    Serial.println(encVal);
    oldEncVal = encVal;
  }
}
