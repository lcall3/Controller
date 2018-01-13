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

