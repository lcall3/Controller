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

// This is a header for the controller implementation
// Parameters for the controller should be chanced in this file
//
// Last edited: 2018-03-20
// Contributor: Muchen He

#ifndef controller_h
#define controller_h

// Includes
#include <Arduino.h>

// [*] Q0 and Q1 PID gain
#define K_P0 1.0f
#define K_I0 0.0f
#define K_D0 0.0f
#define K_P1 1.0f
#define K_I1 0.0f
#define K_D1 0.0f

// [*] Range of motion in pulses
#define YAW_MIN -100
#define YAW_MAX 100
#define PITCH_MIN -50
#define PITCH_MAX 50

// [*] Homing offsets: when motors touche homing switches, the position is reset to these values
#define YAW_HOME_OFFSET -100
#define PITCH_HOME_OFFSET -50

// [*]
#define USE_SERIAL
#define USE_DIGITALREAD
#define USE_PWM_FLOOR

// [*]
#define SERIAL_BAUD_RATE 115200

// [*]
// Timer 1 control
// Prescalers can be 1, 8, 64, 256, 1024
#define TIMER1_PRESCALER 64
#define TIMER1_DESIRED_FREQ 1000
#define TIMER1_MATCH_VALUE = F_CPU / TIMER1_PRESCALER / TIMER1_DESIRED_FREQ

// [*]
#ifdef USE_PWM_FLOOR
#define PWM_FLOOR 30
#endif

// ISR functions
void q0_encoderA_ISR();
void q0_encoderB_ISR();
void q1_encoderA_ISR();
void q1_encoderB_ISR();

// Global variables
// Encoder vars
volatile char vg_q0_encoderA;
volatile char vg_q0_encoderB;
volatile char vg_q1_encoderA;
volatile char vg_q1_encoderB;
volatile int vg_q0_delta_pos;
volatile int vg_q1_delta_pos;

// Tracked speed
volatile int vg_q0_speed;
volatile int vg_q1_speed;

// Tracked position
volatile int vg_q0_pos;
volatile int vg_q1_pos;

// Desired position
int q0_desired;
int q1_desired;

// current desired index
unsigned int g_desired_index;

// Accumulated position error
long g_q0_accum_error;
long g_q1_accum_error;

// Unsigned counter
volatile unsigned long vg_time_vector_count;

// ISR timed control flags
#ifdef USE_SERIAL
volatile char vg_output_serial;
#endif
volatile char vg_control_flag;

// Main state machine
enum states {s_home_q0, s_home_q1, s_run, s_halt};
char g_state;
char g_halt;

// === === ===[ Function prototypes ]=== === ===
void control_motor(char, int);
void stop_all();
void apply_control();
void compute_vertices(float *, float *, int *, int *);

#endif