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

#include "PinChangeInterrupt.h"

#include "controller.h"
#include "lcall3.h"

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

void setup() {

}

void loop() {

}