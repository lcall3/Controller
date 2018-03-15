#define NUM_SAMPLE 10

int samples[NUM_SAMPLE] = {};

// TEST 1 ::: ISR read and update position
volatile byte q0_encoderA, q0_encoderB;
volatile long q0_encoder_pos_change;
void testISRPortRead() {
    q0_encoderB  = PIND & (1 << 5);
    q0_encoderA ^ q0_encoderB ? q0_encoder_pos_change++ : q0_encoder_pos_change--;
}

// TEST 2 ::: ISR read and update position using digitalRead
void testISRDigitalRead() {
    q0_encoderB  = digitalRead(5);
    q0_encoderA ^ q0_encoderB ? q0_encoder_pos_change++ : q0_encoder_pos_change--;
}

// TEST 3 ::: Floating point to integer converison
void testFloatToInt() {
    int x = int(6.7549584);
}

// TEST 4 ::: Serial print 10 characters
void testSerial10Char() {
    Serial.print("123456789");
}

// Run test helper function
void runFunction(void (*fut)(), char testName[]) {
    Serial.print(testName);
    Serial.println(":");

    // Run test
    for (int i = 0; i < NUM_SAMPLE; i++) {
        uint32_t startTime = micros();

        // Run the test function
        fut();

        uint32_t endTime = micros();
        samples[i] = endTime - startTime;
    }

    for (int i = 0; i < NUM_SAMPLE; i++) {
        Serial.print(samples[i], DEC);
        Serial.print(" ");
    }

    Serial.println("\n");
}

void setup() {
    Serial.begin(115200);

    // Run tests
    runFunction(&testISRPortRead, "ISR with pin reading from port register");
    runFunction(&testISRDigitalRead, "ISR with pin reading from digitalRead()");
    runFunction(&testFloatToInt, "Speed of conversio from float to int");
    runFunction(&testSerial10Char, "Speed of serial print for 10 characters");
}

void loop() { }
