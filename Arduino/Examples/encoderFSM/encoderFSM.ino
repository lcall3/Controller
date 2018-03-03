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

// Encoder states and interrupt bytes
volatile int encoder_pos;
volatile byte encoder_state;
volatile byte encoder_next_state;
byte encoder_mask;

// Speed sensing
volatile bool speed_changed = false;
volatile int speed;

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

// Timer 1 compare ISR
ISR(TIMER1_COMPA_vect) {
    speed = encoder_pos;
    speed_changed = true;
    encoder_pos = 0;
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
    // 3125        = 16 MHz     / 256       / 1000 Hz
    OCR1A = 3125;

    // CTC (clear timer on compare match) mode
    TCCR1B |= (1 << WGM12);

    // Set 256 prescaler
    // Prescalers can be 1, 8, 64, 256, 1024
    TCCR1B |= (1 << CS12);

    // Enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
}

void setup() {
    // Reset values
    encoder_pos = 0;
    encoder_state = 0;

    // Turn off all interrupts
    noInterrupts();

    // Set encoder mask to 0110 0000 to only read from pin 5 and 6
    encoder_mask = 1 << (encoderA_pin + 1) | 1 << (encoderB_pin + 1);

    // Set encoder input interrupts
    pinMode(encoderA_pin, INPUT);
    pinMode(encoderB_pin, INPUT);
    attachPCINT(digitalPinToPCINT(encoderA_pin), encoder_ISR, CHANGE);
    attachPCINT(digitalPinToPCINT(encoderB_pin), encoder_ISR, CHANGE);
    
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
        speed_changed = false;
    }
}