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

/*
 * Feedback implementation using pin change interrupts
 */

#include "PinChangeInterrupt.h"

#define encoder0_A_pin 5
#define encoder0_B_pin 6

volatile int16_t encoder0_pos = 0;
uint8_t encoder0_A_in = 0;
uint8_t encoder0_B_in = 0;

bool changed = false;

void encoder0_A_ISR() {
    encoder0_A_in ^ encoder0_B_in ? encoder0_pos++ : encoder0_pos--;
    encoder0_A_in = digitalRead(encoder0_A_pin);
    changed = true;
}

void encoder0_B_ISR() {
    encoder0_B_in = digitalRead(encoder0_B_pin);
    encoder0_B_in ^ encoder0_A_in ? encoder0_pos++ : encoder0_pos--;
    changed = true;
}

void setup() {
    pinMode(encoder0_A_pin, INPUT);
    pinMode(encoder0_B_pin, INPUT);
    attachPCINT(digitalPinToPCINT(encoder0_A_pin), encoder0_A_ISR, CHANGE);
    attachPCINT(digitalPinToPCINT(encoder0_B_pin), encoder0_B_ISR, CHANGE);
    Serial.begin(9600);
    Serial.println("PCINT Rotary Encoder Test");
}

int time;
bool done = false;
void loop() {
    if (changed) {
        Serial.println(encoder0_pos);
        changed = false;
    }

    if (millis() <= 1) {
        time++;
    } else if (done == false) {
        Serial.println(time);
        done = true;
    }
}

