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

// This example shows how to read the ports without using digitalread
// The ATMega328P has three ports (x):
//      B (digital pin 8 to 13)
//      C (analog input pins)
//      D (digital pin 0 to 7)
// 
// Port registers:
// DDRx     Data direction register (read/write)
// PORTx    Data register (read/write)
// PINx     Input pins register (read/write)
// 
// WARNING: ONLY USE BIT MANIPULATION FOR:
//      -   Time sensitivity application, pins need to be read or wrote quickly
//      -   Set/read multiple output/input pins at the same time
//      -   Program size is a constraint
// 
// WARNING: Do not manipulate PORTB upper two bits (they are external crystal pins)
// WARNING: Do not manipulate PORTD pin 0 or pin 1 manually (they are TX and RX for Serial)

byte portState;

void setup() {
    // Sets pin 2 (PORTD) as output
    // This is the same as using the function pinMode(xx, OUTPUT);
    DDRD |= 1 << 2;

    // Sets pin 3 (PORTD) as input
    // This is the same as using the function pinMode(xx, INPUT);
    DDRD &= ~(1 << 3);

    // Set pin 2 to HIGH
    PORTD |= 1 << 2;

    // Read port D
    portState = PIND;

    // Reading bits in port, set pin 2 to LOW if pin 3 is HIGH`
    if (portState & (1 << 3))
        PORTD &= ~(1 << 2);
}

void loop() {
}