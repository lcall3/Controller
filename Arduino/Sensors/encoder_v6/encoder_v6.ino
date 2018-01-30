#include <Encoder.h>
#include <EnableInterrupt.h>

Encoder DUT(5, 6);
long encoder_pos = 0;

void encoder_ISR() {
    encoder_pos = DUT.read();
}

void setup() {
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    Serial.begin(9600);
    Serial.println("Testing for rotary encoder");

    enableInterrupt(5, encoder_ISR, CHANGE);
    enableInterrupt(6, encoder_ISR, CHANGE);
}

void loop() {
    long new_pos = DUT.read();
    if (new_pos != encoder_pos) {
        Serial.println(new_pos);
        encoder_pos = new_pos;
    }
}

