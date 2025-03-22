// -*- C++ -*-
//  Teensy4.1のEEPROMを扱うユーティリティプログラム
//
#include <Arduino.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>
#include "imxrt.h"

char cha,cmnd[81],lbf[81];
int  cp ;
const char *pgname = "Teensy EEPROM Ver1.20";

void software_reset() {
    SCB_AIRCR = 0x05FA0004;
}
  
void setup(void) {
    Serial.begin(115200);
    Serial.println();
    Serial.println(pgname);
    sprintf(lbf,"Builtin EEPROM SIZE 0-%03XH(%d bytes)",EEPROM.length()-1,EEPROM.length());
    switch(EEPROM.length()) {
        case 128:
            Serial.println(F("Teensy LC"));
            break;
        case 512:
            Serial.println(F("Teensy 1.0"));
            break;
        case 1024:
            Serial.println(F("Teensy 2.0"));
            break;
        case 1080:
            Serial.println(F("Teensy 4.0"));
            break;
        case 2048:
            Serial.println(F("Teensy++ 1.0,3.0,3.1,3.2"));
            break;
        case 4096:
            Serial.println(F("Teensy++ 2.0,3.5,3.6"));
            break;
        case 4284:
            Serial.println(F("Teensy 4.1"));
            break;
        default:
            Serial.println(lbf);
            break;
    }
    Serial.println(lbf);
    cha = (char)NULL;
    cp  = 0;
}

void loop(void) {
    bool reading;
    extern void cmnd_dump(String,int);
    extern void cmnd_setbyte(String,int);
    extern void cmnd_fill(String,int);

    String s;
    reading = true;
    cp = 0;
    Serial.print("% ");
    Serial.flush();
    while(reading) {
        if (Serial.available() > 0) {
            cha = Serial.read();
            if ((cha>=0x20)&&(cha<=0x7e)) {
                cmnd[cp] = (char)cha;
                Serial.print(cha);
                cp++;
            } else if (cha==0x08) {
                if (cp>0) {
                    cmnd[cp] = (char)NULL;
                    Serial.write(0x08);
                    Serial.print(" ");
                    Serial.write(0x08);
                    cp--;
                }
            } else if ((cha==0x0a)||(cha==0x0d)) {
                reading = false;
                Serial.println();
                cmnd[cp] = (char)NULL;
                s = String(cmnd);
            }
        }
    }
    if (s.indexOf("dump")==0) {
        cmnd_dump(s,-1);
    } else if (s.indexOf("setb")==0) {
        cmnd_setbyte(s,-1);
    } else if (s.indexOf("fill")==0) {
        cmnd_fill(s,-1);
    } else if (s.indexOf("reset")==0) {
        software_reset();
    } else if (s.indexOf("exit")==0) {
        Serial.println(F("Bye!"));
        delay(1000);
        software_reset();
    } else {
        Serial.println(F("Unknown command"));
    }
}
