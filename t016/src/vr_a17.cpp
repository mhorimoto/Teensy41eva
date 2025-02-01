#include <Arduino.h>

#define VR  A17

void setup() {
    Serial.begin(115200);
    pinMode(VR,INPUT);
    Serial.println("START READ A17");
}

void loop() {
    int a17out;
    a17out = analogRead(VR);
    Serial.print("ANALOG READ=");
    Serial.println(a17out);
    delay(500);
}