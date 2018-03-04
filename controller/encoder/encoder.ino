/* This encoder test code is for PEC12R-4017F-N0024
 *  
 */

const byte PULSES_PER_REV = 24;

const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;
volatile uint16_t pulses = 0;
volatile bool changed = false;

void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(interruptPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
    Serial.begin(9600);
}

void loop() {
    digitalWrite(ledPin, state);
    if (changed) {
        Serial.println(pulses * 360.0 / (24.0 * 2));
        changed = false;
    }
}

void blink() {
    state = !state;
    pulses++;
    changed = true;
}
