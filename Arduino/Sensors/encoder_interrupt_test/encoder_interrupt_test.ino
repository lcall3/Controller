/* Using pin change interrupts
 *
 */

#include "PinChangeInterrupt.h"

#define encoder0_A_pin 5
#define encoder0_B_pin 6

volatile int16_t encoder0_pos = 0;
uint8_t encoder0_A_in = 0;
uint8_t encoder0_B_in = 0;

bool changed = false;

void encoder0_A_ISR() {
    encoder0_A_in ^ encoder0_B_in ? encoder0_pos++ : encoder0_pos--;
    encoder0_A_in = digitalRead(encoder0_A_pin);
    changed = true;
}

void encoder0_B_ISR() {
    encoder0_B_in = digitalRead(encoder0_B_pin);
    encoder0_B_in ^ encoder0_A_in ? encoder0_pos++ : encoder0_pos--;
    changed = true;
}

void setup() {
    pinMode(encoder0_A_pin, INPUT);
    pinMode(encoder0_B_pin, INPUT);
    attachPCINT(digitalPinToPCINT(encoder0_A_pin), encoder0_A_ISR, CHANGE);
    attachPCINT(digitalPinToPCINT(encoder0_B_pin), encoder0_B_ISR, CHANGE);
    Serial.begin(9600);
    Serial.println("PCINT Rotary Encoder Test");
}

void loop() {
    if (changed) {
        Serial.println(encoder0_pos);
        changed = false;
    }
}
