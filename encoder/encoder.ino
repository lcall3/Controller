/* This encoder test code is for PEC12R-4017F-N0024
 *  
 */

const byte interruptPin = 2;
volatile byte state = LOW;
volatile uint16_t pulses = 0;
volatile bool changed = false;

void setup() {
    pinMode(13, OUTPUT);
    pinMode(interruptPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
    Serial.begin(115200);
}

void loop() {
    digitalWrite(13, state);
    if (changed) {
        Serial.println(pulses);
        changed = false;
    }
}

void blink() {
    state = !state;
    pulses++;
    changed = true;
}
