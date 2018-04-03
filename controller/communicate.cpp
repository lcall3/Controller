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

// This is the implementation that outlines all the functions that's required to
// communicate with the host computer
//
// Last edited: 2018-03-27
// Contributor: Muchen He

#include "communicate.h"
#include <Arduino.h>

int parse_array ( int **x, int **y, unsigned int **t, unsigned char **laser) {
    // input byte from serial port
    char inputByte;

    // value buffers
    int sign = 1;
    int bufferX, bufferY, bufferT;

    // output array 
    int arrayLength = 0;
    int index = 0;

    // reading mode
    unsigned char readMode = rm_length;

    while (1) {
        if (Serial.available()) {
            // read incoming serial and echo back
            inputByte = Serial.read();
            Serial.write(inputByte);

            /* check for special characters */

            // start of array 
            if (inputByte == START_ARRAY) {
                readMode = rm_x;

                // reset values
                bufferX = 0;
                bufferY = 0;
                bufferT = 0;
                sign    = 1;
                // reset array index
                index   = 0;

                // free array memory
                free(*x);
                free(*y);
                free(*t);
                free(*laser);

                // allocate array memory
                *x = (int *) malloc(arrayLength * (sizeof(int)));
                *y = (int *) malloc(arrayLength * (sizeof(int)));
                *t = (unsigned int *) malloc(arrayLength * (sizeof(unsigned int)));
                *laser = (unsigned char *) malloc(arrayLength * (sizeof(unsigned char)));

                for (int i = 0; i < arrayLength; i++) {
                  *(*laser + index) = 1;
                }
            }

            // start of next value
            else if (inputByte == ARRAY_SEPARATE) {
                // multiply by +/- sign
                // and move to next value
                if (readMode == rm_x) {
                    bufferX  = bufferX * sign;
                    readMode = rm_y;
                }
                else if (readMode == rm_y) {
                    bufferY  = bufferY * sign;
                    readMode = rm_time;
                }

                // reset sign
                sign = 1;
            }

            // start of next array entry
            else if (inputByte == NEXT_ENTRY) {
                readMode = rm_x;

                // store buffer values into array
                *(*x + index) = bufferX;
                *(*y + index) = bufferY;
                *(*t + index) = bufferT * sign;

                index++;

                // reset buffer
                bufferX = 0;
                bufferY = 0;
                bufferT = 0;
                sign    = 1;
            }

            // end of array 
            else if (inputByte == END_ARRAY) {
                return arrayLength;
            }

            /* read incoming data */

            else if (inputByte == '-' || (inputByte >= '0' && inputByte <= '9')) {  
                // check reading mode
                switch (readMode) {
                    // read array length
                    case rm_length:
                        arrayLength = (arrayLength * 10) + (inputByte - '0');
                    break;

                    // read bufferX
                    case rm_x:
                        if (inputByte == '-')
                            sign = -1;
                        else
                            bufferX = (bufferX * 10) + (inputByte - '0');
                    break;

                    // read Y
                    case rm_y:
                        if (inputByte == '-')
                            sign = -1;
                        else
                            bufferY = (bufferY * 10) + (inputByte - '0');
                    break;

                    // read time
                    case rm_time:
                        if (inputByte == '-')
                            sign = -1;
                        else
                            bufferT = (bufferT * 10) + (inputByte - '0');
                    break;
                }
            }

            /* invalid character */
            else {
                return 0;
            }
        
        }
    }
}
