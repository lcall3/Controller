void setup() {
    Serial.begin(115200);
}

void loop() {
    // if (Serial.available() > 0) {
    //     Serial.println(Serial.readString());
    // }

    delay(500);
    Serial.print(millis() / 1000);
    Serial.print('$');
}