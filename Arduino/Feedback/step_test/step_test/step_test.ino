/*
 * Feedback implementation using pin change interrupts
 */

#include "PinChangeInterrupt.h"

// Test mode
#define TEST_TOGGLE_MODE
#define SAMPLE_TIME = 1;   // (ms)

// Pin definitions
#define encoder0_A_pin 5
#define encoder0_B_pin 6
#define motor0_direc1 7
#define motor0_direc2 8
#define motor0_en 9

// Interrupt variables
volatile long encoder0_pos = 0;
volatile bool encoder0_A_in = 0;
volatile bool encoder0_B_in = 0;
volatile bool changed = false;

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
    Serial.println("\n###");
    
}

int count_time = 0;
int target_pos = 0;
int motor0_en_value;
int motor0_en_value_adj;
const float motor0_K_p = 0.14;

#ifdef TEST_TOGGLE_MODE
int test_toggle_time = 600;
const int motor0_K_p_offset = 12;
int track_time = 0;
#endif

void loop() {
    if (count_time != millis()) {
        Serial.println(encoder0_pos);

        // Control code (to be executed per millisecond)
        #ifdef TEST_TOGGLE_MODE
        // Toggles position every second
        if (track_time > test_toggle_time) {
            if (target_pos == 0) {
                target_pos = 400;
            } else {
                target_pos = 0;
            }
            track_time = 0;
        } else {
            track_time++;
        }
        #endif

        count_time = millis();
    }

    // Controller code that runs as fast as possible
    #ifdef TEST_TOGGLE_MODE
    motor0_en_value = constrain((target_pos - encoder0_pos) * motor0_K_p, -50, 50);

    if (motor0_en_value < 0) {
        // Flip direction first
        digitalWrite(motor0_direc1, LOW);
        digitalWrite(motor0_direc2, HIGH);
        analogWrite(motor0_en, (-motor0_en_value) + motor0_K_p_offset);
    } else {
        digitalWrite(motor0_direc1, HIGH);
        digitalWrite(motor0_direc2, LOW);
        analogWrite(motor0_en, motor0_en_value + motor0_K_p_offset);
    }
    #endif
}

