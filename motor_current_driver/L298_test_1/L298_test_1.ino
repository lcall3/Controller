void setup() {
  pinMode(3, OUTPUT);
}

short PWM = 0;
void loop() {
  analogWrite(3, PWM);
  PWM = PWM == 255 ? 0 : PWM + 1;
  delay(50);
}
