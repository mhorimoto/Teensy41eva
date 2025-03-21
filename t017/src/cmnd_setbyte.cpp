#include <Arduino.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>

void cmnd_setbyte(String p,int at) {
    unsigned int addr,ofs1,ofs2;
    char lbf[80];
    String q;
    byte d,v,buf[10];
    
    ofs1 = p.indexOf(" ");
    ofs2 = p.indexOf(" ",ofs1+1);
    if (ofs1>0) {  // アドレス引数がある
        q = p.substring(ofs1,ofs2);
        q.toCharArray(&buf[0],7);
        addr = (unsigned int)strtol(buf,NULL,16);
        
        if (at==-1) { // EEPROM with CPU
            if (addr >= EEPROM.length()) {
                sprintf(lbf,"EEPROM Address %04XH is Overflow.\n",addr);
                Serial.print(lbf);
                return;
            }
        }
        if (ofs2>0) { // データ引数がある
            q = p.substring(ofs2);
            q.toCharArray(&buf[0],4);
            d = (int)strtol(buf,NULL,16);
            sprintf(lbf,"[%04XH]<=%02XH",addr,d);
            Serial.println(lbf);
            if (at==-1) {
                v = EEPROM.read(addr);
                if (v!=d) {
                    EEPROM.write(addr,d);
                    Serial.println("DONE");
                } else {
                    Serial.println("NO WRITE,SAME DATA");
                }
            }
        } else {
            Serial.println(F("ERROR NO DATA"));
        }
    } else {
        Serial.println(F("ERROR NO ADDR"));
    }
}
