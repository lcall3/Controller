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

// Parsing serial input from web app
//
//
// Last edited: 2018-03-27

// Defined special characters 
#define START_ARRAY '@'
#define ARRAY_SEPARATE ','
#define NEXT_ENTRY '&'
#define END_ARRAY '!'
#define ARRAY_LENGTH '#'

// input byte from serial port
char inputByte;

// value buffers
int sign;
int x, y, t;

// output array 
int arrayLength;
int index;
int *x_out, *y_out, *t_out;

// reading mode
unsigned char readMode;
enum {
    rm_length,
    rm_x,
    rm_y,
    rm_time
};

/*
 * This function prints out the arrays for X, Y, and time vector
 * Parameters: X array, Y array, time vector array, length of array
 * Returns: void
 *
 */
void printData (int x_out[], int y_out[], int t_out[], int arrayLength) {
    Serial.println();
    for (int i = 0; i < arrayLength; i++) {
        Serial.print(x_out[i]);
        Serial.print(" ");
        Serial.print(y_out[i]);
        Serial.print(" ");
        Serial.println(t_out[i]);
    }
}

// setup 
void setup() {
    Serial.begin(115200);

    // reset readMode to 0
    readMode = rm_length;
}

// loop
void loop() {
    if (Serial.available()) {
        // read incoming serial and echo back
        inputByte = Serial.read();
        Serial.write(inputByte);

        // check for special characters
        switch (inputByte) {
        // length of incoming array
        case ARRAY_LENGTH:
            readMode = rm_length;
            arrayLength = 0;
        break;

        // start of array 
        case START_ARRAY:
            readMode = rm_x;

            // reset values
            x    = 0;
            y    = 0;
            t    = 0;
            sign = 1;
            // reset array index
            index = 0;

            // allocate array memory
            x_out = (int *) malloc(arrayLength * (sizeof(int)));
            y_out = (int *) malloc(arrayLength * (sizeof(int)));
            t_out = (int *) malloc(arrayLength * (sizeof(int)));

        break;

        // start of next value
        case ARRAY_SEPARATE:
            // multiply by +/- sign
            // and move to next value
            if (readMode == rm_x) {
                x = x * sign;
                readMode = rm_y;
            }
            else if (readMode == rm_y) {
                y = y * sign;
                readMode = rm_time;
            }

            // reset sign
            sign = 1;
        break;

        // start of next array entry
        case NEXT_ENTRY:
            readMode = rm_x;

            // store buffer values into array
            x_out[index] = x;
            y_out[index] = y;
            t_out[index] = t * sign;

            index++;

            // reset buffer
            x    = 0;
            y    = 0;
            t    = 0;
            sign = 1;
        break;

        // end of array 
        case END_ARRAY:
            // prints out array elements
            printData(x_out, y_out, t_out, arrayLength);
        break;

        // case for any non-special characters
        default: 
            // check reading mode
            switch (readMode) {
                // read array length
            case rm_length:
                arrayLength = (arrayLength * 10) + (inputByte - '0');
            break;

            // read X
            case rm_x:
                if (inputByte == '-')
                    sign = -1;
                else
                    x = (x * 10) + (inputByte - '0');
            break;

            // read Y
            case rm_y:
                if (inputByte == '-')
                    sign = -1;
                else
                    y = (y * 10) + (inputByte - '0');
            break;

            // read time
            case rm_time:
                if (inputByte == '-')
                    sign = -1;
                else
                    t = (t * 10) + (inputByte - '0');
            break;
            }
        break;
        }
    }
}

