const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;

void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(interruptPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
    Serial.begin(9600);
}

void loop() {
    digitalWrite(ledPin, state);
    
}

void blink() {
    state = !state;
}
