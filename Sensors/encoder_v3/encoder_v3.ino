// This doesnt use hardware pull up / debounce

#include <Encoder.h>

Encoder knob(2, 3);

void setup() {
    Serial.begin(9600);
}

long encoderPos = 0;

void loop() {
    long newPos;
    newPos = knob.read();
    if (newPos != encoderPos) {
        Serial.println(newPos / 96.0);
        encoderPos = newPos;
    }
}

