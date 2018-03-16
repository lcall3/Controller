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

#include <Encoder.h>
#include <EnableInterrupt.h>

Encoder DUT(5, 6);
long encoder_pos = 0;

void encoder_ISR() {
    encoder_pos = DUT.read();
}

void setup() {
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    Serial.begin(9600);
    Serial.println("Testing for rotary encoder");

    enableInterrupt(5, encoder_ISR, CHANGE);
    enableInterrupt(6, encoder_ISR, CHANGE);
}

void loop() {
    long new_pos = DUT.read();
    if (new_pos != encoder_pos) {
        Serial.println(new_pos);
        encoder_pos = new_pos;
    }
}

