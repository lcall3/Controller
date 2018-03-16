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

// This sketch takes vertices of desired locations,
// then convert it into angles and ultimately pulses of the encoders

#include "hline.h"

void setup() {
    Serial.begin(115200);
    for (int i = 0; i < N_VERTICES; i++) {
        Serial.print(vertices_x[i]);
        Serial.print("\t");
        Serial.print(vertices_y[i]);
        Serial.print("\t");
        Serial.println(time_vector[i]);
    }
}

void loop() {

}