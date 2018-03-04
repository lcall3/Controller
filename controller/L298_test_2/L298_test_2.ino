void setup() {
    pinMode(3, OUTPUT);
    Serial.begin(9600);
}

String msg;
int pwm = 0;
void loop() {
    if (Serial.available()  > 0) {
        msg = Serial.readString();
        pwm = msg.toInt();
        Serial.println(pwm, DEC);
    }
    analogWrite(3, pwm);
}