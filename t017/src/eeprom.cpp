// -*- C++ -*-
//  Teensy4.1のEEPROMを扱うユーティリティプログラム
//
#include <Arduino.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>

char cha,cmnd[81],lbf[81];
int  cp ;
const char *pgname = "EEPROM Ver1.00";

void setup(void) {
    Serial.begin(115200);
    Serial.println(pgname);
    sprintf(lbf,"Builtin EEPROM SIZE 0-%03XH(%d bytes)",EEPROM.length()-1,EEPROM.length());
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
    }
}
