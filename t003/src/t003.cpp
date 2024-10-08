#include <Arduino.h>

void setup(void) {
    pinMode(33,OUTPUT);
}

void loop(void) {
  int x;
  for (x=0;x<255;x++) {
    analogWrite(33,x);
    delay(10);
  }
  for (x=255;x>0;x--) {
    analogWrite(33,x);
    delay(10);
  }
  delay(10);  
}
