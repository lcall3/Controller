//##########################################################################
//
// lcall3 Controller is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// lcall3 Controller is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with lcall3 Controller. If not, see <http://www.gnu.org/licenses/>.
// 
//##########################################################################

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
#define USE_DIGITAL_READ_   // [*]
#define UNIT_SQUARE         // [*]

// PID Limiter
#ifdef LIMIT_PWM
#define K_MIN 38    // [*]
#define K_MAX 80    // [*]
#endif

// Square step response
#ifdef UNIT_SQUARE
#define UNIT_SQUARE_CYCLE_TIME 500 // [*]
#define UNIT_SQUARE_CYCLE_TIME_1 75 // [*]
int cycle_time;
#endif

// PID Values
#define P_GAIN 1.7f    // [*]
#define D_GAIN -48.0f    // [*]
#define I_GAIN 0.000f      // [*]

// Initial PWM Value for Homing
#define INIT_PWM 60

// Pins
#define Q0_ENCODER_A 5          // PORTD 5
#define Q0_ENCODER_B 6          // PORTD 6
#define Q0_EN_PIN 11
#define Q0_DIR_A A0             // Using analog pins as digital IO
#define Q0_DIR_B A1
#define Q0_HOME 7               // Homing pin
#define DEMO_TOGGLE 10

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

    // cycle_time = (digitalRead(DEMO_TOGGLE) == HIGH) ? UNIT_SQUARE_CYCLE_TIME : UNIT_SQUARE_CYCLE_TIME_1;
    if (digitalRead(DEMO_TOGGLE)) {
        cycle_time = UNIT_SQUARE_CYCLE_TIME;
    } else {
        cycle_time = UNIT_SQUARE_CYCLE_TIME_1;
    }

    // State
    state = 0;

    scounter = 0;
    output_serial = false;

    #ifdef UNIT_SQUARE
    toggle_unit_square = false;
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
    Serial.begin(9600);
}

void loop() {

    // INIT STATE
    if (state == 0) {
        q0_pwm = INIT_PWM;
        digitalWrite(Q0_DIR_A, 1);
        digitalWrite(Q0_DIR_B, 0);
        // Send PWM output
        analogWrite(Q0_EN_PIN, q0_pwm);
        while (digitalRead(Q0_HOME) == HIGH);
        // Set to OPERATING STATE
        state = 1;
        q0_position = 88;
    }

    // OPERATING STATE
    else {
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
            digitalWrite(Q0_DIR_A, q0_pwm > 0);
            digitalWrite(Q0_DIR_B, q0_pwm < 0);
            q0_pwm = abs(q0_pwm);

            // Limit PWM
            #ifdef LIMIT_PWM
            q0_pwm = constrain(q0_pwm, K_MIN, K_MAX);
            #endif

            // Send PWM output
            analogWrite(Q0_EN_PIN, q0_pwm);
        }

        // Send to Serial when output flag is enabled
        if (output_serial) {
            Serial.println(q0_position, DEC);
            output_serial = false;
        }

        // Change desired position when its corresponding flag is enabled
        #ifdef UNIT_SQUARE
        if (toggle_unit_square) {
            if (digitalRead(DEMO_TOGGLE) == HIGH) {
                if (q0_desired_pos > 0) {
                    q0_desired_pos = -TEST_STEP_DESIRED_POS;
                } else {
                    q0_desired_pos = TEST_STEP_DESIRED_POS;
                }
            } else {
                if (q0_desired_pos > 0) {
                    q0_desired_pos = -TEST_STEP_DESIRED_POS_1;
                } else {
                    q0_desired_pos = TEST_STEP_DESIRED_POS_1;
                }
            }
            
            toggle_unit_square = false;
        }
        #endif
    }
}
