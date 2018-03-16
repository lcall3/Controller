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

// Implementation of the Controller
// This file is the controller entry points
//
// Last edited: 2018-03-16
// Contributor: Muchen He

#include "PinChangeInterrupt.h"

#include "controller.h"
#include "lcall3.h"
#include "experimental.h"

/* Timer 1 compare output ISR
 * Performs data acquisition and other controller flags
 *
 * EXEC TIME:   8-12us
 */
ISR(TIMER1_COMPA_vect) {
    // Update motor 0
    vg_q0_pos      += vg_q0_delta_pos;
    vg_q0_speed     = vg_q0_delta_pos;
    vg_q0_delta_pos = 0;

    // Update motor 1
    vg_q1_pos      += vg_q1_delta_pos;
    vg_q1_speed     = vg_q1_delta_pos;
    vg_q1_delta_pos = 0;

    // Control flag
    vg_control_flag = true;

    // Update counter
    vg_counter++;
}

/* Encoder edge change interrupt service routines
 * These ISR are attached to Pin Change Interrupts from encoder pins
 *
 * EXEC TIME:   4-8us each
 */
void q0_encoderA_ISR() {
    vg_q0_encoderA ^ vg_q0_encoderB ? vg_q0_delta_pos++ : vg_q0_delta_pos--;
    #ifdef USE_DIGITALREAD
    vg_q0_encoderA = digitalRead(ENCODER0_A);
    #else
    vg_q0_encoderA = PIND & (1 << ENCODER0_A);      // FIXME: change port to match pin assignment
    #endif
}
void q0_encoderB_ISR() {
    #ifdef USE_DIGITALREAD
    vg_q0_encoderB = digitalRead(ENCODER0_B);
    #else
    vg_q0_encoderB  = PIND & (1 << ENCODER0_B);     // FIXME: change port to match pin assignment
    #endif
    vg_q0_encoderA ^ vg_q0_encoderB ? vg_q0_delta_pos++ : vg_q0_delta_pos--;
}
void q1_encoderA_ISR() {
    vg_q1_encoderA ^ vg_q1_encoderB ? vg_q1_delta_pos++ : vg_q1_delta_pos--;
    #ifdef USE_DIGITALREAD
    vg_q1_encoderA = digitalRead(ENCODER1_A);
    #else
    vg_q1_encoderA = PIND & (1 << ENCODER1_A);      // FIXME: change port to match pin assignment
    #endif
}
void q1_encoderB_ISR() {
    #ifdef USE_DIGITALREAD
    vg_q1_encoderB = digitalRead(ENCODER1_B);
    #else
    vg_q1_encoderB  = PIND & (1 << ENCODER1_B);     // FIXME: change port to match pin assignment
    #endif
    vg_q1_encoderA ^ vg_q1_encoderB ? vg_q1_delta_pos++ : vg_q1_delta_pos--;
}

/* This function initializes the register that controls timer 1
 * Timer 1 is set to compare match ouput
 *
 * EXEC TIME:   N/A
 */
inline void init_timer1() {
    // Rest timer 1 control
    TCCR1A = 0;
    TCCR1B = 0;

    // Reset timer 1 value
    TCNT1 = 0;

    // Set output compare value
    // Match value = Clock Freq / Prescaler / Desired Freq
    // 250         = 16 MHz     / 64        / 1000 Hz
    OCR1A = TIMER1_MATCH_VALUE;

    // CTC (clear timer on compare match) mode
    TCCR1B |= (1 << WGM12);

    // Set 64 prescaler
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS11);

    // Enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
}

/* Setup function that runs once at the very begging
 *
 * EXEC TIME:   N/A
 */
void setup() {
    // Reset and initialze values
    vg_q0_encoderA   = 0;
    vg_q0_encoderB   = 0;
    vg_q1_encoderA   = 0;
    vg_q1_encoderB   = 0;
    vg_q0_delta_pos  = 0;
    vg_q1_delta_pos  = 0;
    vg_q0_speed      = 0;
    vg_q1_speed      = 0;
    vg_q0_pos        = 0;
    vg_q1_pos        = 0;
    g_q0_accum_error = 0;
    g_q1_accum_error = 0;
    vg_counter       = 0;
    vg_control_flag  = 0;

    #ifdef USE_SERIAL
    vg_output_serial = 0;
    #endif

    // Initial state
    g_state = s_home_q0;

    // Stop motor movements
    stopAll();

    // === === ===[ Set pin mode ]=== === ===
    // Encoder pins
    pinMode(ENCODER0_A, INPUT);
    pinMode(ENCODER0_B, INPUT);
    pinMode(ENCODER1_A, INPUT);
    pinMode(ENCODER1_B, INPUT);

    // Attach interrupt pins
    attachPCINT(digitalPinToPCINT(ENCODER0_A), q0_encoderA_ISR, CHANGE);
    attachPCINT(digitalPinToPCINT(ENCODER0_B), q0_encoderB_ISR, CHANGE);
    attachPCINT(digitalPinToPCINT(ENCODER1_A), q1_encoderA_ISR, CHANGE);
    attachPCINT(digitalPinToPCINT(ENCODER1_B), q1_encoderB_ISR, CHANGE);

    // Current driver output
    pinMode(MOTOR0_EN, OUTPUT);
    pinMode(MOTOR1_EN, OUTPUT);
    // === === ===[ End of set pin mode ]=== === ===

    // Initialize timer 1
    init_timer1();

    // Enable all interrupts
    interrupts();

    // Enable serial
    #ifdef USE_SERIAL
    Serial.begin(SERIAL_BAUD_RATE);
    #endif
}

/* Main program loop
 * Contains the main state machine for motor controller
 *
 * EXEC TIME:   N/A
 */
void loop() {
    switch(g_state) {
        case s_home_q0:
            // This state should move motor 0 until it is homed
            controlMotor(MOTOR0_EN, MOTOR0_MIN_MOVE_PWM);
            if (digitalRead(HOMING0)) {
                g_state = s_home_q1;
                stopAll();
            }
        break;
        case s_home_q1:
            // This state should move motor 1 until it is homed
            controlMotor(MOTOR1_EN, MOTOR1_MIN_MOVE_PWM);
            if (digitalRead(HOMING1)) {
                g_state = s_run;
                stopAll();
            }
        break;
        case STATE_RUN:
            if (g_halt) {
                g_state = s_halt;
            }

            // TODO: finish state machine
        break;
        case s_halt:
            g_state = s_halt;
        break;
        default:
            g_state = s_halt;
        break;
    }
}

/* Use analogWrite to control each of the motors
 *
 * PARAM motor: motor enable pins of the motor we want to control
 * PARAM pwm:   desired motor pwm to be sent
 *
 * EXEC TIME:   
 */
void controlMotor(char motor, int pwm) {
    if (motor == MOTOR0_EN) {

        // Set direction of motor movement
        digitalWrite(MOTOR0_DIREC, pwm > 0);

        // Set pwm
        #ifdef USE_PWM_FLOOR
        pwm = constrain(abs(pwm), PWM_FLOOR, 255);
        #else
        pwm = abs(pwm);
        #endif

        // Write to pin
        analogWrite(MOTOR0_EN, pwm);
        
    } else if (motor == MOTOR1_EN) {
        digitalWrite(MOTOR1_DIREC, pwm > 0);
        #ifdef USE_PWM_FLOOR
        pwm = constrain(abs(pwm), PWM_FLOOR, 255);
        #else
        pwm = abs(pwm);
        #endif
        analogWrite(MOTOR1_EN, pwm);
    }
}

/* Use analogWrite to control each of the motors
 *
 * EXEC TIME:   12us
 */
void stopAll() {
    analogWrite(MOTOR0_EN, 0);
    analogWrite(MOTOR1_EN, 0);
}