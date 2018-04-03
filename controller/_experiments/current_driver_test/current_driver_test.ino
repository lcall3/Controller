#define Q0_EN_PIN 5
#define Q0_DIR_A A1
#define Q0_DIR_B A3

String input_pwm;
int pwm;
String input_direc;
int direc;

void setup() {

      // Serial
    Serial.begin(115200);
    
  pinMode(Q0_EN_PIN, OUTPUT);
     while (Serial.available() == 0);
   
        // Read PWM
        input_pwm = Serial.readString();
        pwm = input_pwm.toInt();

        // Acknowledge pwm value
        Serial.print("received: ");
        Serial.println(pwm, DEC);

        // Write to motor
        analogWrite(Q0_EN_PIN, pwm);
}

void loop() {
  if (Serial.available() > 0 ) {
    input_direc = Serial.readString();
    direc = input_direc.toInt();
  }
    Serial.println(direc, DEC);
    digitalWrite(Q0_DIR_A, direc);
    digitalWrite(Q0_DIR_B, (!direc));
}
