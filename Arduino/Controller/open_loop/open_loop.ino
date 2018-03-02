/*
 * This tests the open loop response and outputs speed of rotation
 */

#include "PinChangeInterrupt.h"

// Parameters
#define PULSE_PER_REV 400   // Pulses per revolution of encoder
#define SAMPLE_DELAY 10     // How long to wait to sample rotation (ms)

// Pins
#define encoderA_pin 5
#define encoderB_pin 6

// Encoder and interrupt variables
long last_encoder_pos;
volatile long encoder_pos;
volatile bool encoderA;
volatile bool encoderB;
volatile bool changed = false;

// Timing variables
unsigned long previous_millis;
unsigned long current_millis;

void encoderA_ISR() {
    encoderA ^ encoderB ? encoder_pos++ : encoder_pos--;
    // TODO: Use anything else but digitalRead to reduce ISR time
    encoderA = digitalRead(encoderA_pin);
    changed = false;
}

void encoderB_ISR() {
    encoderB = digitalRead(encoderB_pin);
    encoderB ^ encoderA ? encoder_pos++ : encoder_pos--;
    changed = false;
}

void setup() {
    pinMode(encoderA_pin, INPUT);
    pinMode(encoderB_pin, INPUT);
    attachPCINT(digitalPinToPCINT(encoderA_pin), encoderA_ISR, CHANGE);
    attachPCINT(digitalPinToPCINT(encoderB_pin), encoderB_ISR, CHANGE);
    Serial.begin(9600);

    // Initialize values
    last_encoder_pos = 0;
}

void loop() {
    // Only exceute calculation every 100ms
    unsigned long current_millis = millis();
    if (current_millis - previous_millis >= SAMPLE_DELAY) {
        previous_millis = current_millis;
        Serial.println(sample_speed());
    }
}

long sample_speed() {
    // Returns the rotation speed of the motor in pulses/ms
    long delta_pos = encoder_pos - last_encoder_pos;
    last_encoder_pos = encoder_pos;
    return delta_pos;
}