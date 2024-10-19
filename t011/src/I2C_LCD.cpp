/*
 * display to LCD
 */
#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define SW1 14
#define SW2 15
#define SW3 16

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

bool s1,s2,s3;
volatile bool t1,t2,t3;
int p1=0,p2=0,p3=0;

void lcd_setup(void) {
  extern void pushsw1(void),pushsw2(void),pushsw3(void);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(115200);
  pinMode(SW1,INPUT_PULLUP);
  pinMode(SW2,INPUT_PULLUP);
  pinMode(SW3,INPUT_PULLUP);
  Serial.begin(115200);
  t1 = digitalRead(SW1);
  t2 = digitalRead(SW2);
  t3 = digitalRead(SW3);
  attachInterrupt(digitalPinToInterrupt(SW1),pushsw1,FALLING);
  attachInterrupt(digitalPinToInterrupt(SW2),pushsw2,FALLING);
  attachInterrupt(digitalPinToInterrupt(SW3),pushsw3,FALLING);
  lcd.print("M306 T011 V1.20");
  lcd.setCursor(0,1);
  lcd.print("000");
}

void pushsw1(void) {
    delay(5);
    int s1 = digitalRead(SW1);
    if (s1==t1) {
      t1 = 1;
      Serial.println("t1=Push");
      p1 = (p1==0)?1:0;
      lcd.setCursor(0,1);
      lcd.print(p1);
      t1 = 0;
    }
}
void pushsw2(void) {
    delay(5);
    int s2 = digitalRead(SW2);
    if (s2==t2) {
      t2 = 1;
      Serial.println("t2=Push");
      p2 = (p2==0)?1:0;
      lcd.setCursor(1,1);
      lcd.print(p2);
      t2 = 0;
    }
}
void pushsw3(void) {
    delay(5);
    int s3 = digitalRead(SW3);
    if (s3==t3) {
      t3 = 1;
      Serial.println("t3=Push");
      p3 = (p3==0)?1:0;
      lcd.setCursor(2,1);
      lcd.print(p3);
      t3 = 0;
    }
}
