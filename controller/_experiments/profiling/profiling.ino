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

// TEST 5 ::: Timer ISR function
long pos = 0;
int pos_change = 300;
int speed;
boolean flag1, flag2;
long counter;
void testTimer1ISR() {
    pos       += pos_change;
    speed      = pos_change;
    pos_change = 0;
    flag1 = true;
    flag2 = true;
    counter = 0;
    counter++;
}

// TEST 6 ::: Timer ISR function for dual motors
long pos2 = 0;
int pos_change2 = -365;
int speed2;
void testTimer1ISR2() {
    pos       += pos_change;
    speed      = pos_change;
    pos_change = 0;
    pos2      += pos_change2;
    speed2     = pos_change2;
    pos_change = 0;
    flag1 = true;
    flag2 = true;
    counter = 0;
    counter++;
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
    runFunction(&testTimer1ISR, "Timer 1 ISR single motor");
    runFunction(&testTimer1ISR2, "Timer 1 ISR dual motor");
}

void loop() { }