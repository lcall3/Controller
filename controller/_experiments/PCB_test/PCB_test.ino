// This sketch is the final sketch. Hopefully. 
// This is for the base motor
//
// Last edited: 2018-03-07
// Contributor: Muchen He

#include "PinChangeInterrupt.h"

// Parameters
#define PULSE_PER_REV 400           // [*] Pulses per revolution of encoder
#define TEST_STEP_DESIRED_POS 60    // [*] Desired position
#define TEST_STEP_DESIRED_POS_1 5
#define SERIAL_DELAY 5             // [*] Number of count before serial is sent

// Testing flags (put '_' at the end to turn the flag off)
#define LIMIT_PWM           // [*]
#define USE_DIGITAL_READ   // [*]
#define UNIT_SQUARE         // [*]

// PID Limiter
#ifdef LIMIT_PWM
#define K_MIN 38    // [*]
#define K_MAX 255    // [*]
#endif

// Square step response
#ifdef UNIT_SQUARE
#define UNIT_SQUARE_CYCLE_TIME 500 // [*]
#define UNIT_SQUARE_CYCLE_TIME_1 75 // [*]
int cycle_time;
#endif

// PID Values
#define P_GAIN 100.7f    // [*]
#define D_GAIN -48.0f    // [*]
#define I_GAIN 0.000f      // [*]

// Initial PWM Value for Homing
#define INIT_PWM 60


// Pins
#define Q0_ENCODER_A 10          // PORTD 5
#define Q0_ENCODER_B 9          // PORTD 6
#define Q0_EN_PIN 5
#define Q0_DIR_A A1             // Using analog pins as digital IO
#define Q0_DIR_B A3
#define Q0_HOME A2               // Homing pin

// PWN control
int q0_pwm;

// Encoder and interrupt variables
volatile bool q0_encoderA;
volatile bool q0_encoderB;
volatile int q0_encoder_pos_change;

// Encoder speed
volatile int q0_speed;

// Tracked position
volatile long q0_position;

// Desired position
int q0_desired_pos;

// Error Accumulator
long int q0_accum;

// Serial counter
volatile uint16_t scounter;

/// ISR Control flags
volatile boolean output_serial;
volatile boolean control_flag;
#ifdef UNIT_SQUARE
volatile boolean toggle_unit_square;
#endif


// State Machine
char state;

// External (pin change) interrupt service routines
void q0_encoderA_ISR() {
    q0_encoderA ^ q0_encoderB ? q0_encoder_pos_change++ : q0_encoder_pos_change--;
    #ifdef USE_DIGITAL_READ
    q0_encoderA = digitalRead(Q0_ENCODER_A);
    #else
    q0_encoderA = PIND & (1 << Q0_ENCODER_A);
    #endif
}

void q0_encoderB_ISR() {
    #ifdef USE_DIGITAL_READ
    q0_encoderB = digitalRead(Q0_ENCODER_B);
    #else
    q0_encoderB  = PIND & (1 << Q0_ENCODER_B);
    #endif
    q0_encoderA ^ q0_encoderB ? q0_encoder_pos_change++ : q0_encoder_pos_change--;
}

// Timer 1 compare ISR
ISR(TIMER1_COMPA_vect) {
    q0_position          += q0_encoder_pos_change;
    q0_speed              = q0_encoder_pos_change;
    q0_encoder_pos_change = 0;

    // Control flag
    control_flag = true;

    // Change flags based on counter value
    if (scounter % SERIAL_DELAY == 0)
        output_serial = true;

    #ifdef UNIT_SQUARE
    if (scounter % cycle_time == 0) {
        toggle_unit_square = true;
        scounter = 0;
    }
    #endif

    // Update counter
    scounter++;
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
    q0_desired_pos        = TEST_STEP_DESIRED_POS;
    q0_accum              = 0;
    state = 0;

    scounter = 0;
    output_serial = true;

    #ifdef UNIT_SQUARE
    toggle_unit_square = false;
    #endif

    // Set encoder input interrupts
    pinMode(Q0_ENCODER_A, INPUT);
    pinMode(Q0_ENCODER_B, INPUT);
    attachPCINT(digitalPinToPCINT(Q0_ENCODER_A), q0_encoderA_ISR, CHANGE);
    attachPCINT(digitalPinToPCINT(Q0_ENCODER_B), q0_encoderB_ISR, CHANGE);

    // #ifdef Q0_USING_CURRENT_DRIVER
    pinMode(Q0_EN_PIN, OUTPUT);
    pinMode(Q0_DIR_A, OUTPUT);
   //  #endif
    
    // Initiate timer 1
   init_timer1();

    // Enable all interrupts
   interrupts();

    // Serial
    Serial.begin(9600);
}

void loop() {
      // Compute control PWM
      if (control_flag) {
          control_flag = false;

          // Integrate position error
          q0_accum += (q0_desired_pos - q0_position);

          // Compute PWM
          q0_pwm  = int(P_GAIN * (q0_desired_pos - q0_position));
          q0_pwm += D_GAIN * q0_speed;
          q0_pwm += I_GAIN * q0_accum;

          // Set direction and abs PWM
          // digitalWrite(Q0_DIR_A, q0_pwm > 0);
          digitalWrite(A1, HIGH);
          digitalWrite(A3, LOW);
          q0_pwm = abs(q0_pwm);

          // Limit PWM
          #ifdef LIMIT_PWM
          q0_pwm = constrain(q0_pwm, K_MIN, K_MAX);
          #endif

          // Send PWM output
          analogWrite(Q0_EN_PIN, 255); //**
      }

      // // Send to Serial when output flag is enabled
      if (output_serial) {
          Serial.println(q0_position, DEC);
          output_serial = false;
      }
}
