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
// Last edited: 2018-03-15
// Contributor: Muchen He

#ifndef controller_h
#define controller_h

// Includes
#include <Arduino.h>

// Comment out to disable
#define USE_SERIAL
#define USE_DIGITALREAD

// ISR functions
void q0_encoderA_ISR();
void q0_encoderB_ISR();
void q1_encoderA_ISR();
void q1_encoderB_ISR();

// Global variables
volatile char vg_q0_encoderA;
volatile char vg_q0_encoderB;
volatile char vg_q1_encoderA;
volatile char vg_q1_encoderB;
volatile int vg_q0_delta_pos;
volatile int vg_q1_delta_pos;
volatile int vg_q0_speed;
volatile int vg_q1_speed;

// Tracked position
volatile int vg_q0_pos;
volatile int vg_q1_pos;

// Accumulated position error
long g_q0_accum_error;
long g_q1_accum_error;

// Unsigned counter
volatile unsigned int vg_counter;

// Timer 1 control
// Prescalers can be 1, 8, 64, 256, 1024
#define TIMER1_PRESCALER 64
#define TIMER1_DESIRED_FREQ 1000
#define TIMER1_MATCH_VALUE = F_CPU / TIMER1_PRESCALER / TIMER1_DESIRED_FREQ

// ISR timed control flags
#ifdef USE_SERIAL
volatile char vg_output_serial;
#endif
volatile char vg_control_flag;

// Main state machine
#define STATE_HOME_Q0_WAIT 0
#define STATE_HOME_Q0_REPOS 1
#define STATE_HOME_Q1_WAIT 2
#define STATE_HOME_Q1_REPOS 3
#define STATE_RUN 4
#define STATE_HALT 5
char g_state;

#endif