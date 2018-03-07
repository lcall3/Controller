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

/* This encoder test code is for PEC12R-4017F-N0024
 *  
 */

const byte PULSES_PER_REV = 24;

const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;
volatile uint16_t pulses = 0;
volatile bool changed = false;

void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(interruptPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
    Serial.begin(9600);
}

void loop() {
    digitalWrite(ledPin, state);
    if (changed) {
        Serial.println(pulses * 360.0 / (24.0 * 2));
        changed = false;
    }
}

void blink() {
    state = !state;
    pulses++;
    changed = true;
}
