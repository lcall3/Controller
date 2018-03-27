// This experiment echos the command received from p5 serial socket

void setup() {
    Serial.begin(115200);
}

int inputByte;
void loop() {
    if (Serial.available()) {
        inputByte = Serial.read();
        Serial.write(inputByte);
    }
}
