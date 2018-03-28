#include "communicate.h"

/* This function prints out the arrays for X, Y, and time vector
 * Parameters: X array, Y array, time vector array, length of array
 * Returns: void
 *
 */

  int arr_length;
  int *x, *y;
  unsigned int *t;

  

void setup(){
  Serial.begin(115200);
}

void loop() {


  arr_length = parse_array(&x, &y, &t);

  Serial.println(arr_length);
  printData(x, y, t, arr_length);

}
