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
// Last edited: 2018-03-27
// Contributor: Muchen He

#include "PinChangeInterrupt.h"

#include "controller.h"
#include "lcall3.h"
#include "experimental.h"
#include "communicate.h"

//#define _SKIP_SHAPE
//#define _SERIAL_DEBUG

#ifdef _SKIP_SHAPE
int g_vertices_x[] = { 10, 10, -10, -10 };
int g_vertices_y[] = { -20, 20, 20, -20 };
unsigned int g_vertices_time[] = { 100, 100, 100, 100 };
unsigned char g_n_vertices = 4;
#else
// Shape array
int *g_vertices_x;
int *g_vertices_y;
unsigned int *g_vertices_time;
unsigned int g_n_vertices;
#endif

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
    vg_time_vector_count++;
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
    vg_q0_encoderA = PINB & 0x04;
    #endif
}
void q0_encoderB_ISR() {
    #ifdef USE_DIGITALREAD
    vg_q0_encoderB = digitalRead(ENCODER0_B);
    #else
    vg_q0_encoderB = PINB & 0x02;
    #endif
    vg_q0_encoderA ^ vg_q0_encoderB ? vg_q0_delta_pos++ : vg_q0_delta_pos--;
}
void q1_encoderA_ISR() {
    vg_q1_encoderA ^ vg_q1_encoderB ? vg_q1_delta_pos++ : vg_q1_delta_pos--;
    #ifdef USE_DIGITALREAD
    vg_q1_encoderA = digitalRead(ENCODER1_A);
    #else
    vg_q1_encoderA = PIND & 0x01;
    #endif
}
void q1_encoderB_ISR() {
    #ifdef USE_DIGITALREAD
    vg_q1_encoderB = digitalRead(ENCODER1_B);
    #else
    vg_q1_encoderB = PIND & 0x80;
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
    vg_q0_encoderA       = 0;
    vg_q0_encoderB       = 0;
    vg_q1_encoderA       = 0;
    vg_q1_encoderB       = 0;
    vg_q0_delta_pos      = 0;
    vg_q1_delta_pos      = 0;
    vg_q0_speed          = 0;
    vg_q1_speed          = 0;
    vg_q0_pos            = 0;
    vg_q1_pos            = 0;
    g_q0_accum_error     = 0;
    g_q1_accum_error     = 0;
    vg_time_vector_count = 0;
    vg_control_flag      = 0;
    vg_output_serial_flag = 0;

    g_state = s_home_q0;

    // Initial desired
    g_desired_index = 0;

    // Stop motor movements
    stop_all();

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

    // Homing pins
    pinMode(HOMING0, INPUT);
    pinMode(HOMING1, INPUT);

    // Button pins
    pinMode(BTN_A, INPUT_PULLUP);
    pinMode(BTN_B, INPUT_PULLUP);
    // === === ===[ End of set pin mode ]=== === ===

    // Initialize timer 1
    init_timer1();

    // Enable all interrupts
    interrupts();

    // Enable serial
    Serial.begin(SERIAL_BAUD_RATE);
}

/* Main program loop
 * Contains the main state machine for motor controller
 *
 * EXEC TIME:   N/A
 */
char test;
void loop() {
//    #ifdef _SERIAL_DEBUG
//    Serial.print(g_state, DEC);
//    Serial.print(' ');
//    #endif

    switch(g_state) {
        case s_idle:
            g_state = s_home_q0;
        break;
        case s_home_q0:
            // This state should move motor 0 until it is homed
            control_motor(MOTOR0_EN, 120);

            if (analogRead(HOMING0) > 1000) {
                g_state = s_listen; //g_state = s_home_q1;
                stop_all();

                // Reset position
                vg_q0_pos = YAW_HOME_OFFSET;
            }
        break;
        case s_home_q1:
            // This state should move motor 1 until it is homed
            control_motor(MOTOR1_EN, -220);

            // Put yaw motor to position 0
            apply_control(true);

            // Poll for when laser hits the sensor
            if (analogRead(HOMING1) > 500) {
                g_state = s_listen;
                stop_all();

                // Rest position
                vg_q1_pos = -PITCH_HOME_OFFSET;
            }
        break;
        case s_listen:
            #ifndef _SKIP_SHAPE
            if (Serial.available()) {
                char in = Serial.read();

                // Controller to do certain tasks when listening
                switch(in) {
                    case PARSE_ARRAY:
                        g_n_vertices = parse_array(&g_vertices_x, &g_vertices_y, &g_vertices_time);
                        if (g_n_vertices > 0) {

                            // Array parsed correctly, go to draw
                            g_state = s_draw;
                        };
                    break;
                    case IMMEDIATE_POS:
                        // TODO:
                    break;
                }
            }
            #endif

            // FIXME:
            g_state = s_draw;
        break;
        case s_draw:

            // Normal controller code
            apply_control(false);

            // Check for stop signal
            if (Serial.available()) {
                if (Serial.read() == STOP_DRAW) {
                    g_state = s_listen;
                }
            }
        break;
        default:
            // Should never be here, reset if needed
            setup();
        break;
    }
}

/* Use analogWrite to control each of the motors
 *
 * PARAM motor: motor enable pins of the motor we want to control
 * PARAM pwm: desired motor signed pwm (-255 to 255) to be sent
 *
 * EXEC TIME: 20us
 */
void control_motor(char motor, long pwm) {
    if (motor == MOTOR0_EN) {

        // Set direction of motor movement
        if (pwm > 0) {
            digitalWrite(MOTOR0_DIRECA, HIGH);
            digitalWrite(MOTOR0_DIRECB, LOW);
        } else {
            digitalWrite(MOTOR0_DIRECA, LOW);
            digitalWrite(MOTOR0_DIRECB, HIGH);
        }

        // Set pwm
        pwm = constrain(abs(pwm), PWM_FLOOR, 255);

        #ifdef _SERIAL_DEBUG
        Serial.println(pwm, DEC);
        #endif

        // Write to pin
        analogWrite(MOTOR0_EN, pwm);
        
    } else if (motor == MOTOR1_EN) {

        if (pwm > 0) {
            digitalWrite(MOTOR1_DIRECA, HIGH);
            digitalWrite(MOTOR1_DIRECB, LOW);
        } else {
            digitalWrite(MOTOR1_DIRECA, LOW);
            digitalWrite(MOTOR1_DIRECB, HIGH);
        }

        pwm = constrain(abs(pwm), PWM_FLOOR, 255);
        analogWrite(MOTOR1_EN, pwm);
    }
}

/* Use analogWrite to control each of the motors
 *
 * EXEC TIME: 12us
 */
inline void stop_all() {
    analogWrite(MOTOR0_EN, 0);
    analogWrite(MOTOR1_EN, 0);
}

/* Apply the PID control to both motors
 * TODO: the desired positions be abstracted outside of this function
 *
 * EXEC TIME: 190us
 */
inline void apply_control(bool is_homing) {
    // Only control when control flag is set to true
    if (!vg_control_flag) return;

    // Only apply a specific position to q0
    if (is_homing) {
        int q0_error = -vg_q0_pos;
        g_q0_accum_error += q0_error;

        long q0_pwm = long((K_P0 * q0_error) + (K_D0 * vg_q0_speed) + (K_I0 * g_q0_accum_error));
        control_motor(MOTOR0_EN, q0_pwm);

        return;
    }
    
    // Check that vertices array is well-formed
    if (g_vertices_x == NULL || g_vertices_y == NULL || g_vertices_time == NULL || g_n_vertices <= 0) return;

    // Update time vg_time_vector_count
    // Update desire index based on time elapsed
    if (vg_time_vector_count >= g_vertices_time[g_desired_index]) {
        if (g_desired_index == g_n_vertices - 1) {
            g_desired_index = 0;
        } else {
            g_desired_index++;
        }
        vg_time_vector_count = 0;
    }

    // Get desired position
    q0_desired = g_vertices_x[g_desired_index];
    q1_desired = g_vertices_y[g_desired_index];

    // Get error
    int q0_error = q0_desired - vg_q0_pos;
    int q1_error = q1_desired - vg_q1_pos;

    // Accumulate integral error
    g_q0_accum_error += q0_error;
    g_q1_accum_error += q1_error;

    // Compute signed PWM
    long q0_pwm = long((K_P0 * q0_error) + (K_D0 * vg_q0_speed) + (K_I0 * g_q0_accum_error));
    long q1_pwm = long((K_P1 * q1_error) + (K_D1 * vg_q1_speed) + (K_I1 * g_q1_accum_error));

    #ifdef _SERIAL_DEBUG
    Serial.print(q1_desired, DEC);
    Serial.print(' ');
    Serial.print(vg_q1_pos, DEC);
    Serial.print(' ');
    Serial.print(q1_pwm, DEC);
    Serial.print(' ');
    #endif

    // Send pwm to motors
    control_motor(MOTOR0_EN, q0_pwm);
    control_motor(MOTOR1_EN, q1_pwm);


    // Reset control flag
    vg_control_flag = false;
}
