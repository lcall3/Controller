/*
 * Feedback implementation using pin change interrupts
 */

#include "PinChangeInterrupt.h"

// Pin definitions
#define encoder0_A_pin 5
#define encoder0_B_pin 6
#define motor0_direc1 7
#define motor0_direc2 8
#define motor0_en 9

volatile int16_t encoder0_pos = 0;
uint8_t encoder0_A_in = 0;
uint8_t encoder0_B_in = 0;

bool changed = false;

const int SAMPLE_TIME = 1;   // (ms)

// Encoder ISRs
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

    // Motor output pins
    pinMode(motor0_direc1, OUTPUT);
    pinMode(motor0_direc2, OUTPUT);
    pinMode(motor0_en, OUTPUT);

    // Create an array to store the step response
    Serial.println("###");
    
}

int count_time = 0;
bool checked = false;
void loop() {
    if (count_time != millis()) {
        Serial.println(encoder0_pos);
        count_time = millis();
    }

    // Controller code that runs as fast as possible
    
}

