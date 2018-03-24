#include <Wire.h>
#include <avr/pgmspace.h>

#include "OLED.hpp"

String inputString;
boolean stringComplete = false;

void setup() {
    Wire.begin();
    oled.init();
    oled.clearDisplay();
    oled.setNormalDisplay();
    oled.setVerticalMode();
    oled.setGrayLevel(255);

    Serial.begin(115200);
    // oled.setTextXY(1, 0);
    for (int i = 0; i < 12; i++) {
        oled.setTextXY(i, 0);
        oled.setGrayLevel(255);
        oled.putString("Goodbye Sleep");
    }
    oled.setTextXY(1, 0);
}

void loop() {
    if (Serial.available() > 0) {
        String msg = Serial.readString();
        Serial.println(msg);
        oled.putString(msg.c_str());
    }
}