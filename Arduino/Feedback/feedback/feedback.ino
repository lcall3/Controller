/* Integrated testing 1 of motor with encoder
 * 
 */

#define encoder_A_int_pin 2
#define encoder_B_int_pin 3

#define motor_enable_pin 5

volatile int16_t encoder_pos = 0;
uint8_t encoder_A_state = 0;
uint8_t encoder_B_state = 0;

bool changed = false;

void encoder_ISR() {
    encoder_A_state = digitalRead(encoder_A_int_pin);
    encoder_B_state = digitalRead(encoder_B_int_pin);

    if ((encoder_A_state == HIGH && encoder_B_state == LOW) ||
        (encoder_A_state == LOW && encoder_B_state == HIGH))
        encoder_pos++;
    else if ((encoder_A_state == HIGH && encoder_B_state == HIGH) ||
             (encoder_A_state == LOW && encoder_B_state == LOW))
        encoder_pos--;
    changed = true;
}

void setup() {
    pinMode(encoder_A_int_pin, INPUT);
    pinMode(encoder_B_int_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(encoder_A_int_pin), encoder_ISR, CHANGE);

    pinMode(motor_enable_pin, OUTPUT);

    // Serial
    Serial.begin(9600);
}

void loop() {
    analogWrite(motor_enable_pin, 47);
    if (changed) {
        Serial.println(encoder_pos, DEC);
        changed = false;
    }
}
