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

#define encoder0PinA 2
#define encoder0PinB 3

volatile unsigned int encoder0Pos = 0;
unsigned int tmp_Pos = 1;
unsigned int valx;
unsigned int valy;
unsigned int valz;

boolean A_set;
boolean B_set;


void setup() {

  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);

  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

  Serial.begin (9600);
}


void loop() {
  //Check each second for change in position
  if (tmp_Pos != encoder0Pos) {
    Serial.print("Index:"); Serial.print(encoder0Pos, DEC); Serial.print(", Values: ");
    Serial.print(valx, DEC); Serial.print(", ");
    Serial.print(valy, DEC); Serial.print(", ");
    Serial.print(valz, DEC); Serial.println();
    tmp_Pos = encoder0Pos;
  }
  delay(1000);
}


// Interrupt on A changing state
void doEncoderA() {

  // Low to High transition?
  if (digitalRead(encoder0PinA) == HIGH) {
    A_set = true;
    if (!B_set) {
      encoder0Pos = encoder0Pos + 1;
      valx = analogRead(0);
      valy = analogRead(1);
      valz = analogRead(2);
    }
  }

  // High-to-low transition?
  if (digitalRead(encoder0PinA) == LOW) {
    A_set = false;
  }

}


// Interrupt on B changing state
void doEncoderB() {

  // Low-to-high transition?
  if (digitalRead(encoder0PinB) == HIGH) {
    B_set = true;
    if (!A_set) {
      encoder0Pos = encoder0Pos - 1;
    }
  }

  // High-to-low transition?
  if (digitalRead(encoder0PinB) == LOW) {
    B_set = false;
  }
}
