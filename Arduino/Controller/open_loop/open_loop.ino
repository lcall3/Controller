// This open loop sketch takes the open loop response

#include "PinChangeInterrupt.h"

// Parameters
#define PULSE_PER_REV 400       // Pulses per revolution of encoder

// Pins
#define Q0_ENCODER_A 5          // PORTD 5
#define Q0_ENCODER_B 6          // PORTD 6

// Encoder and interrupt variables
volatile bool encoderA;
volatile bool encoderB;
volatile int encoder_pos_change;

// Encoder speed
volatile int speed;
volatile bool speed_changed;

// External (pin change) interrupt service routines
void q0_encoderA_ISR() {
    encoderA ^ encoderB ? encoder_pos_change++ : encoder_pos_change--;

    // Read encoder A
    encoderA = PIND & (1 << 5);
}

void q0_encoderB_ISR() {
    // Read encoder B
    encoderB  = PIND & (1 << 6);
    encoderA ^ encoderB ? encoder_pos_change++ : encoder_pos_change--;
}

// Timer 1 compare ISR
ISR(TIMER1_COMPA_vect) {
    speed = encoder_pos_change;
    speed_changed = true;
    encoder_pos_change = 0;
}

// Timer1 compare output setup function
inline void init_timer1() {
    // Rest timer 1 control
    TCCR1A = 0;
    TCCR1B = 0;

    // Reset timer 1 value
    TCNT1 = 0;

    // Set output compare value
    // Match value = Clock Freq / Prescaler / Desired Freq
    // 625         = 16 MHz     / 256       / 100 Hz
    OCR1A = 625;

    // CTC (clear timer on compare match) mode
    TCCR1B |= (1 << WGM12);

    // Set 256 prescaler
    TCCR1B |= (1 << CS12);

    // Enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
}

void setup() {
    // Reset values
    encoderA = false;
    encoderB = false;
    encoder_pos_change = 0;
    speed = 0;
    speed_changed = false;

    // Turn off all interrupts
    noInterrupts();

    // Set encoder input interrupts
    pinMode(encoderA_pin, INPUT);
    pinMode(encoderB_pin, INPUT);
    attachPCINT(digitalPinToPCINT(encoderA_pin), q0_encoderA_ISR, CHANGE);
    attachPCINT(digitalPinToPCINT(encoderB_pin), q0_encoderB_ISR, CHANGE);
    
    // Initiate timer 1
    init_timer1();

    // Enable all interrupts
    interrupts();

    // Serial
    Serial.begin(115200);
}

void loop() {
    if (speed_changed) {
        Serial.println(speed, DEC);
        speed_changed = 0;
    }
}