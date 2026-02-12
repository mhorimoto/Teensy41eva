#include <Arduino.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>

void cmnd_help(void) {
    Serial.println(F("help"));
    Serial.println(F("  dump [Address in 100H units]"));
    Serial.println(F("           Displays 256 bytes from the specified address. "));
    Serial.println(F("           If the address is omitted, it will display from address 0."));
    Serial.println(F("  setb hex_address hex_data"));
    Serial.println(F("           Write the specified data to the specified address. "));
    Serial.println(F("           If the address is omitted, it will write to address 0."));
    Serial.println(F("  fill hex_start_addr hex_end_addr hex_bytedata"));
    Serial.println(F("           Fill the specified data from the specified start address to the specified end address."));
    Serial.println(F("  reset"));
    Serial.println(F("           Reset the Teensy."));
    Serial.println(F("  help"));
    Serial.println(F("           Display this help."));
    Serial.println(F("  version"));
    Serial.println(F("           Display the version of the Teensy EEPROM utility."));
}