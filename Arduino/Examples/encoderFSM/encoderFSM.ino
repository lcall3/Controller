// This example demonstrates reading encoders using a FSM
// The FSM has 4 states based on the sensor reading:
//      A B State
//      0 0 00
//      0 1 01
//      1 1 11
//      1 0 10
//
// The state transitions follows grey code
//
// The direction of the grey code determines the 
// direction of the rotation of the encoder
//
// The output of the state machine is operations to increment or
// decrement the position counter
//
// If the states go:
//      00->01->11->10
// then decrement the counter
//
// If the states go:
//      00->10->11->01
// then increment the counter

#include "PinChangeInterrupt.h"

// Pins
#define encoderA_pin 5
#define encoderB_pin 6

volatile int encoder_pos;
volatile bool encoderA;
volatile bool encoderB;

void setup() {
    pinMode(encoderA_pin, INPUT);
    pinMode(encoderB_pin, INPUT);
}