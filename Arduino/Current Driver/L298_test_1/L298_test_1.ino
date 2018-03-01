void setup() {
  pinMode(3, OUTPUT);
}

short PWM = 0;
void loop() {
  analogWrite(3, PWM);
  PWM = 100.0 * (sin(millis() / 1000.0) + 1) + 50;
  delay(50);
}