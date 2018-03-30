#define Q0_EN_PIN 11
#define Q0_DIR_A 8
#define Q0_DIR_B 9

String input_pwm;
int pwm;

void setup() {

      // Serial
    Serial.begin(115200);
    
  digitalWrite(Q0_DIR_A, 1);
  digitalWrite(Q0_DIR_B, 0);
  pinMode(Q0_EN_PIN, OUTPUT);
}

void loop() {
   Serial.println(pwm);
   if (Serial.available() > 0) {

        // Read PWM
        input_pwm = Serial.readString();
        pwm = input_pwm.toInt();

        // Acknowledge pwm value
        Serial.print("received: ");
        Serial.println(pwm, DEC);

        // Write to motor
        analogWrite(Q0_EN_PIN, pwm);
    }
}
