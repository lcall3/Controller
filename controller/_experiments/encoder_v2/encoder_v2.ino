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

/* version 2 of encoder test code for PEC12R-4017F-N0024
 *  
 */

#define encoderA_pin 2
#define encoderB_pin 3

volatile int16_t encoderPos = 0;
uint8_t encoderA_old = 0;
uint8_t encoderB_new = 0;

bool changed = false;

void encoderA_ISR() {
    encoderB_new ^ encoderA_old ? encoderPos++ : encoderPos--;
    encoderA_old = digitalRead(encoderA_pin);
    changed = true;
}

void encoderB_ISR() {
    encoderB_new = digitalRead(encoderB_pin);
    encoderB_new ^ encoderA_old ? encoderPos++ : encoderPos--;
    changed = true;
}

void setup() {
    pinMode(encoderA_pin, INPUT);
    pinMode(encoderB_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(encoderA_pin), encoderA_ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderB_pin), encoderB_ISR, CHANGE);
    Serial.begin(115200);
}

void loop() {
    if (changed) {
        Serial.println(encoderPos);
        changed = false;
    }
}

