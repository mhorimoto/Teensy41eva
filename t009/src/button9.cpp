#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define True  1
#define False 0

#define SW1 14
#define SW2 15
#define SW3 16

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

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

bool s1,s2,s3;
volatile bool t1,t2,t3,bt;
volatile int  c,r;
int p1=0,p2=0,p3=0;
int lc=1 ;

void setup(void) {
    extern void pushsw1(void),pushsw2(void),pushsw3(void);
    extern void pushkcol1(void),pushkcol2(void),pushkcol3(void),pushkcol4(void),
                pushkcol5(void),pushkcol6(void),pushkcol7(void),pushkcol8(void);
    c = 0;
    r = 0;
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
    
    attachInterrupt(digitalPinToInterrupt(SW1),pushsw1,FALLING);
    attachInterrupt(digitalPinToInterrupt(SW2),pushsw2,FALLING);
    attachInterrupt(digitalPinToInterrupt(SW3),pushsw3,FALLING);
//    attachInterrupt(digitalPinToInterrupt(KCOL1),pushkcol1,HIGH);
//    attachInterrupt(digitalPinToInterrupt(KCOL2),pushkcol2,HIGH);
//    attachInterrupt(digitalPinToInterrupt(KCOL3),pushkcol3,HIGH);
//    attachInterrupt(digitalPinToInterrupt(KCOL4),pushkcol4,HIGH);
//    attachInterrupt(digitalPinToInterrupt(KCOL5),pushkcol5,HIGH);
//    attachInterrupt(digitalPinToInterrupt(KCOL6),pushkcol6,HIGH);
//    attachInterrupt(digitalPinToInterrupt(KCOL7),pushkcol7,HIGH);
//    attachInterrupt(digitalPinToInterrupt(KCOL8),pushkcol8,HIGH);
    lcd.print("M306 T009 V1.20");
    lcd.setCursor(0,1);
    lcd.print("000 0x0");
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
        t1 = 0;
    }
    if (t2) {
        Serial.println("t2=Push");
        p2 = (p2==0)?1:0;
        lcd.setCursor(1,1);
        lcd.print(p2);
        t2 = 0;
    }
    if (t3) {
        Serial.println("t3=Push");
        p3 = (p3==0)?1:0;
        lcd.setCursor(2,1);
        lcd.print(p3);
        t3 = 0;
    }
    if (bt) {
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

int chkkrow(int tcol) {
    int col,i,row;
    col = tcol+32;
    bt = True;
    Serial.println("INT");
    for (i=1;i<5;i++) {
        digitalWrite(i+19,LOW);
        delay(5);
        if (digitalRead(col)==LOW) {
            digitalWrite(i+19,HIGH);
            return(i);
        }
    }
    return(0);
}

void pushkcol1(void) {
    delay(50);
    int v = digitalRead(KCOL1);
    if (v!=HIGH) return;
    c = 1;
    bt = True;
}

void pushkcol2(void) {
    delay(50);
    int v = digitalRead(KCOL2);
    if (v!=HIGH) return;
    c = 2;
    bt = True;
}

void pushkcol3(void) {
    delay(50);
    int v = digitalRead(KCOL3);
    if (v!=HIGH) return;
    c = 3;
    bt = True;
}

void pushkcol4(void) {
    delay(50);
    int v = digitalRead(KCOL4);
    if (v!=HIGH) return;
    c = 4;
    bt = True;
}

void pushkcol5(void) {
    delay(50);
    int v = digitalRead(KCOL5);
    if (v!=HIGH) return;
    c = 5;
    bt = True;
}

void pushkcol6(void) {
    delay(50);
    int v = digitalRead(KCOL6);
    if (v!=HIGH) return;
    c = 6;
    bt = True;
}

void pushkcol7(void) {
    delay(50);
    int v = digitalRead(KCOL7);
    if (v!=HIGH) return;
    c = 7;
    bt = True;
}

void pushkcol8(void) {
    delay(50);
    int v = digitalRead(KCOL8);
    if (v!=HIGH) return;
    c = 8;
    bt = True;
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
