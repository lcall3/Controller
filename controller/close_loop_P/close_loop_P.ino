// This sketch implements a closed loop response for a simple P controller
// This only implements a simple motor

#include "PinChangeInterrupt.h"

// Parameters
#define PULSE_PER_REV 400       // Pulses per revolution of encoder

// Pins
#define Q0_ENCODER_A 5          // PORTD 5
#define Q0_ENCODER_B 6          // PORTD 6
#define Q0_EN_PIN 11
#define Q0_DIR_A A0             // Using analog pins as digital IO
#define Q0_DIR_B A1

// PWN control
int q0_pwm;

// Encoder and interrupt variables
volatile bool q0_encoderA;
volatile bool q0_encoderB;
volatile int q0_encoder_pos_change;

// Encoder speed
volatile int q0_speed;
volatile bool q0_speed_changed;

// Tracked position
volatile long q0_position;

// Serial counter
volatile uint16_t serial_count;

// External (pin change) interrupt service routines
void q0_encoderA_ISR() {
    q0_encoderA ^ q0_encoderB ? q0_encoder_pos_change++ : q0_encoder_pos_change--;

    // Read encoder A
    q0_encoderA = PIND & (1 << Q0_ENCODER_A);
}

void q0_encoderB_ISR() {
    // Read encoder B
    q0_encoderB  = PIND & (1 << Q0_ENCODER_B);
    q0_encoderA ^ q0_encoderB ? q0_encoder_pos_change++ : q0_encoder_pos_change--;
}

// Timer 1 compare ISR
ISR(TIMER1_COMPA_vect) {
    q0_position          += q0_encoder_pos_change;
    q0_speed              = q0_encoder_pos_change;
    q0_speed_changed      = true;
    q0_encoder_pos_change = 0;

    serial_count++;
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
    // 250         = 16 MHz     / 64        / 1000 Hz
    OCR1A = 250;

    // CTC (clear timer on compare match) mode
    TCCR1B |= (1 << WGM12);

    // Set 64 prescaler
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS11);

    // Enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
}

void setup() {
    // Reset values
    q0_encoderA           = false;
    q0_encoderB           = false;
    q0_encoder_pos_change = 0;
    q0_speed              = 0;
    q0_speed_changed      = false;

    serial_count = 0;

    #ifdef Q0_USING_CURRENT_DRIVER
    #endif

    // Set encoder input interrupts
    pinMode(Q0_ENCODER_A, INPUT);
    pinMode(Q0_ENCODER_B, INPUT);
    attachPCINT(digitalPinToPCINT(Q0_ENCODER_A), q0_encoderA_ISR, CHANGE);
    attachPCINT(digitalPinToPCINT(Q0_ENCODER_B), q0_encoderB_ISR, CHANGE);

    #ifdef Q0_USING_CURRENT_DRIVER
    pinMode(Q0_EN_PIN, OUTPUT);
    #endif
    
    // Initiate timer 1
    init_timer1();

    // Enable all interrupts
    interrupts();

    // Serial
    Serial.begin(115200);
}

int q0_desired_pos = 1000;
#define K_MIN 30
#define K_MAX 80
#define P_GAIN 0.05f

void loop() {
    q0_pwm = int(P_GAIN * (q0_desired_pos - q0_position));
    digitalWrite(Q0_DIR_A, q0_pwm > 0);
    digitalWrite(Q0_DIR_B, q0_pwm < 0);
    q0_pwm = constrain(q0_pwm, K_MIN, K_MAX);
    analogWrite(Q0_EN_PIN, q0_pwm);

    if (serial_count == 10) {
        serial_count = 0;
        Serial.println(q0_position, DEC);
    }
}