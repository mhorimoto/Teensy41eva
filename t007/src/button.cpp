#include <Arduino.h>

#define SW1 14
#define SW2 15
#define SW3 16

bool s1,s2,s3;
volatile bool t1,t2,t3;

void setup(void) {
    extern void pushsw1(void),pushsw2(void),pushsw3(void);
    pinMode(SW1,INPUT_PULLUP);
    pinMode(SW2,INPUT_PULLUP);
    pinMode(SW3,INPUT_PULLUP);
    Serial.begin(115200);
    t1 = digitalRead(SW1);
    t2 = digitalRead(SW2);
    t3 = digitalRead(SW3);
    Serial.print("s1=");
    Serial.print("  s2=");
    Serial.print("  s3=");
    Serial.println(t3);
    attachInterrupt(digitalPinToInterrupt(SW1),pushsw1,FALLING);
    attachInterrupt(digitalPinToInterrupt(SW2),pushsw2,FALLING);
    attachInterrupt(digitalPinToInterrupt(SW3),pushsw3,FALLING);
}

void loop(void) {
    if (t1) {
        Serial.println("t1=Push");
        t1 = 0;
    }
    if (t2) {
        Serial.println("t2=Push");
        t2 = 0;
    }
    if (t3) {
        Serial.println("t3=Push");
        t3 = 0;
    }
}

void pushsw1(void) {
    delay(5);
    int s1 = digitalRead(SW1);
    if (s1==t1) t1 = 1;
}
void pushsw2(void) {
    delay(5);
    int s2 = digitalRead(SW2);
    if (s2==t2) t2 = 1;
}
void pushsw3(void) {
    delay(5);
    int s3 = digitalRead(SW3);
    if (s3==t3) t3 = 1;
}
