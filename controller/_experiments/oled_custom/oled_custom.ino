#include <Wire.h>
#include <avr/pgmspace.h>

#include "OLED.hpp"


void setup() {
    Wire.begin();
    oled.init();
    oled.clearDisplay();
    oled.setNormalDisplay();
    oled.setVerticalMode();
    oled.setGrayLevel(255);
}

int i = 0;
void loop() {
    oled.setTextXY(i % 12, 0);
    oled.putString("Bye sleep");
    delay(400);
    i++;
}