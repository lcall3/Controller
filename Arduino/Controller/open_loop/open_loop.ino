// This open loop sketch takes the open loop response
// and samples the angular velocity given a voltage

#include "PinChangeInterrupt.h"

// Parameters
#define PULSE_PER_REV 400       // Pulses per revolution of encoder

// Pins
#define Q0_ENCODER_A 5
#define Q0_ENCODER_B 6

// Encoder and interrupt variables
volatile bool encoderA;
volatile bool encoderB;
volatile int encoder_pos_change;

// External (pin change) interrupt service routines
void q0_encoderA_ISR() {
    encoderA ^ encoderB ? encoder_pos_change++ : encoder_pos_change--;
    encoderA = digitalRead(Q0_ENCODER_A);
}

void q0_encoderB_ISR() {
    encoderB = digitalRead(Q0_ENCODER_B);
    encoderA ^ encoderB ? encoder_pos_change++ : encoder_pos_change--;
}