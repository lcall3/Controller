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
//
// Last edited: 2018-03-14
// Contributor: Muchen He

#ifndef LCALL3_H
#define LCALL3_H

// Pin layouts
// Encoder input pins (uses pin change interrupts)
#define ENCODER0_A 7
#define ENCODER0_B 8
#define ENCODER1_A 9
#define ENCODER1_B 10

// PWM motor control pins
#define MOTOR0_EN 5
#define MOTOR1_EN 6

// Directional control pins
#define MOTOR0_DIREC A0
#define MOTOR1_DIREC A1

// Homing pins
#define HOMING0 A4
#define HOMING1 A5

// Laser control
#define LASER_CONTROL 11

// Communication
#define RX_PIN 0
#define TX_PIN 1

// Misc
#define ONBOARD_LED 13

// Aux
#define AUX_D2 2
#define AUX_D3 3
#define AUX_A2 2
#define AUX_A3 3
#define AUX_A6 6
#define AUX_A7 7

#endif