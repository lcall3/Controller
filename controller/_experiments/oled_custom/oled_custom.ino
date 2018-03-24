#include <Wire.h>
#include <avr/pgmspace.h>

#include "OLED.hpp"


void setup() {
    Wire.begin();
    oled.init();
    oled.clearDisplay();
    oled.setNormalDisplay();
    oled.setVerticalMode();

    for (int i = 0; i < 12; i++) {
        oled.setTextXY(i, 0);
        oled.setGrayLevel(255);
        oled.putString("Goodbye Sleep");
    }
}

void loop() {
}