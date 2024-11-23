#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define True  1
#define False 0

#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0

#include "TeensyTimerInterrupt.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "Teensy_ISR_Timer.h"

#define HW_TIMER_INTERVAL_MS      1L
#define TIMER_INTERVAL_0_01S          1L
#define TIMER_INTERVAL_0_5S           500L
#define TIMER_INTERVAL_1S             1000L
#define TIMER_INTERVAL_1_5S           1500L
#define TIMER_INTERVAL_2S             2000L
#define TIMER_INTERVAL_3S             3000L

#define SW1 14
#define SW2 15
#define SW3 16

#define COL1  24
#define COL2  25
#define COL3  26
#define COL4  27
#define COL5  28
#define COL6  29
#define COL7  30
#define COL8  31

#define ROW1  2
#define ROW2  3
#define ROW3  4
#define ROW4  5

#define KCOL1 33
#define KCOL2 34
#define KCOL3 35
#define KCOL4 36
#define KCOL5 37
#define KCOL6 38
#define KCOL7 39
#define KCOL8 40

#define KROW1 20
#define KROW2 21
#define KROW3 22
#define KROW4 23

// You can select Teensy Hardware Timer  from TEENSY_TIMER_1 or TEENSY_TIMER_3
// Init Teensy timer TEENSY_TIMER_1
TeensyTimer ITimer(TEENSY_TIMER_1);
// Init Teensy_ISR_Timer
// Each Teensy_ISR_Timer can service 16 different ISR-based timers
Teensy_ISR_Timer ISR_Timer;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

bool s1,s2,s3;
volatile bool t1,t2,t3,bt;
volatile int  c,r;
int p1=0,p2=0,p3=0;
int lc=1 ;

int led[8][4] = {};

void TimerHandler()
{
  ISR_Timer.run();
}

void cyclic() {
    int lr,lc;
    for (lr=0;lr<4;lr++) {
        for (lc=0;lc<8;lc++) {
            digitalWrite((lr+ROW1),led[lc][lr]);
            digitalWrite((lc+COL1),led[lc][lr]);
 //           delay(1);
//            if (led[lc][lr]!=0) {
                //digitalWrite((lr+ROW1),HIGH);
                //digitalWrite((lc+COL1),HIGH);
                //delay(10);
                //digitalWrite((lr+ROW1),LOW);
                //digitalWrite((lc+COL1),LOW);
            //}
        }
    }
    
}

void bufprt(void) {
    char tbuf[80];
    Serial.begin(115200);

    for (r=0;r<4;r++) {
        sprintf(tbuf,"%d %d %d %d %d %d %d %d",led[0][r],led[1][r],led[2][r],led[3][r],
                    led[4][r],led[5][r],led[6][r],led[7][r]);
        Serial.println(tbuf);
    }
}

char *ver = "K250 T012 V0.30";

void setup(void) {
    char tbuf[80];
    extern void pushsw1(void),pushsw2(void),pushsw3(void);
    
    c = 0;
    r = 0;

    Serial.begin(115200);
    pinMode(SW1,INPUT_PULLUP);
    pinMode(SW2,INPUT_PULLUP);
    pinMode(SW3,INPUT_PULLUP);
    pinMode(KROW1,OUTPUT);
    pinMode(KROW2,OUTPUT);
    pinMode(KROW3,OUTPUT);
    pinMode(KROW4,OUTPUT);
    pinMode(KCOL1,INPUT_PULLDOWN);
    pinMode(KCOL2,INPUT_PULLDOWN);
    pinMode(KCOL3,INPUT_PULLDOWN);
    pinMode(KCOL4,INPUT_PULLDOWN);
    pinMode(KCOL5,INPUT_PULLDOWN);
    pinMode(KCOL6,INPUT_PULLDOWN);
    pinMode(KCOL7,INPUT_PULLDOWN);
    pinMode(KCOL8,INPUT_PULLDOWN);
    pinMode(COL1, OUTPUT);
    pinMode(COL2, OUTPUT);
    pinMode(COL3, OUTPUT);
    pinMode(COL4, OUTPUT);
    pinMode(COL5, OUTPUT);
    pinMode(COL6, OUTPUT);
    pinMode(COL7, OUTPUT);
    pinMode(COL8, OUTPUT);

    lcd.init();                      // initialize the lcd 
    lcd.backlight();
    Serial.begin(115200);
    t1 = digitalRead(SW1);
    t2 = digitalRead(SW2);
    t3 = digitalRead(SW3);
    Serial.print("s1=");
    Serial.print(t1);
    Serial.print("  s2=");
    Serial.print(t2);
    Serial.print("  s3=");
    Serial.println(t3);
    bt = False;
    digitalWrite(KROW1,LOW);
    digitalWrite(KROW2,LOW);
    digitalWrite(KROW3,LOW);
    digitalWrite(KROW4,LOW);
    
    Serial.println(ver);
    bufprt();
    attachInterrupt(digitalPinToInterrupt(SW1),pushsw1,FALLING);
    attachInterrupt(digitalPinToInterrupt(SW2),pushsw2,FALLING);
    attachInterrupt(digitalPinToInterrupt(SW3),pushsw3,FALLING);
// Interval in microsecs
    if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler)) {
        Serial.print(F("Starting ITimer OK, millis() = ")); Serial.println(millis());
    } else {
        Serial.println(F("Can't set ITimer. Select another freq. or timer"));
    }
    // Just to demonstrate, don't use too many ISR Timers if not absolutely necessary
    // You can use up to 16 timer for each ISR_Timer
    //ISR_Timer.setInterval(TIMER_INTERVAL_1S,  doingSomething1);
    //ISR_Timer.setInterval(TIMER_INTERVAL_2S,  doingSomething2);
    //ISR_Timer.setInterval(TIMER_INTERVAL_3S,  doingSomething3);
    ISR_Timer.setInterval(TIMER_INTERVAL_0_01S,cyclic);
    lcd.print(ver);
    lcd.setCursor(0,1);
    lcd.print("000 0x0");
    led[0][0] = 1;
    led[1][1] = 1;
    led[2][2] = 1;
    led[3][3] = 1;
}

int chkcols(int r) {
    int v;
    delay(50);
    for(v=0;v<8;v++) {
        if (digitalRead(v+33)==HIGH) {
            bt = True;
            return(v+1);
        }
    }
    bt = False;
    return(0);
}
void loop(void) {
    int lc,lr;
    r++;
    if (r>4) r=1;
    digitalWrite(KROW1,LOW);
    digitalWrite(KROW2,LOW);
    digitalWrite(KROW3,LOW);
    digitalWrite(KROW4,LOW);
    switch(r) {
        case 1:
            digitalWrite(KROW1,HIGH);
            c = chkcols(r);
            break;
        case 2:
            digitalWrite(KROW2,HIGH);
            c = chkcols(r);
            break;
        case 3:
            digitalWrite(KROW3,HIGH);
            c = chkcols(r);
            break;
        case 4:
            digitalWrite(KROW4,HIGH);
            c = chkcols(r);
            break;
    }
    if (t1) {
        Serial.println("t1=Push");
        p1 = (p1==0)?1:0;
        lcd.setCursor(0,1);
        lcd.print(p1);
        bufprt();
        t1 = 0;
    }
    if (t2) {
        Serial.println("t2=Push memory clear");
        p2 = (p2==0)?1:0;
        lcd.setCursor(1,1);
        lcd.print(p2);
        t2 = 0;
        for(int x=0;x<8;x++) {
            for (int y=0;y<4;y++) {
                led[x][y] = 0;
            }
        }
    }
    if (t3) {
        Serial.println("t3=Push");
        p3 = (p3==0)?1:0;
        lcd.setCursor(2,1);
        lcd.print(p3);
        t3 = 0;
    }
    if (bt) {
        led[c-1][r-1] = (led[c-1][r-1]==0)? 1:0;
        Serial.print("CR=");
        Serial.print(c);
        Serial.print("x");
        Serial.println(r);
        lcd.setCursor(4,1);
        lcd.print(c);
        lcd.setCursor(6,1);
        lcd.print(r);
        bt = False;
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
