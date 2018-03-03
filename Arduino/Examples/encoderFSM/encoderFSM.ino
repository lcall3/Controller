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
#define encoderA_pin 5      // Corresponds to PORTD 5
#define encoderB_pin 6      // Corresponds to PORTD 6
                            // Using 01100000

volatile int encoder_pos;
volatile byte encoder_state;
volatile byte encoder_next_state;
byte encoder_mask;

// Encoder change ISR
void encoder_ISR() {
    encoder_next_state = PIND & encoder_mask >> 5;
    if (
        (encoder_state == 0x00 & encoder_next_state == 0x01) |
        (encoder_state == 0x01 & encoder_next_state == 0x03) |
        (encoder_state == 0x03 & encoder_next_state == 0x02) |
        (encoder_state == 0x02 & encoder_next_state == 0x00)
    )
        encoder_pos++;
    else if (
        (encoder_state == 0x00 & encoder_next_state == 0x02) |
        (encoder_state == 0x02 & encoder_next_state == 0x03) |
        (encoder_state == 0x03 & encoder_next_state == 0x01) |
        (encoder_state == 0x01 & encoder_next_state == 0x00)
    )
        encoder_pos--;
}

void setup() {
    // Reset values
    encoder_pos = 0;
    encoder_state = 0;

    // Set encoder mask to 0110 0000 to only read from pin 5 and 6
    encoder_mask = 1 << (encoderA_pin + 1) | 1 << (encoderB_pin + 1);

    // Set encoder input interrupts
    pinMode(encoderA_pin, INPUT);
    pinMode(encoderB_pin, INPUT);
    attachPCINT(digitalPinToPCINT(encoderA_pin), encoder_ISR, CHANGE);
    attachPCINT(digitalPinToPCINT(encoderB_pin), encoder_ISR, CHANGE);

    // Serial
    Serial.begin(9600);
}