// This is an example that shows the timer interrupt functionality on the Arduino
// This example uses TIMER 1 compare match interrupt
// Alternatively, one could use the timer overflow interrupt
// But everytime an overflow occurs, the timer needs to be preloaded for timing

// ======[ Timer registers ]======
// TCCRx    Timer/Counter control registers
// TCNTx    Timer/Counter register (value of timer/counter)
// OCRx     Output compare register
// ICRx     Input capture register (only for 16bit register)
// TIMSKx   Interrupt mask register (enable/disable timer interrupts)
// TIFRx    Interrupt flag register (indicate pending timer interrupts)

#define LED_PIN 13

// This function initiates timer 1 and its interrupts
inline void init_timer1() {
    // Reset timer 1 controls
    TCCR1A = 0;
    TCCR1B = 0;

    // Reset timer 1 count
    TCNT1 = 0;

    // Set output compare value
    // Match value = Clock Freq / Prescaler / Desired Freq
    // 31250       = 16 MHz     / 256       / 2 Hz
    OCR1A = 31250;

    // CTC (clear timer on compare match) mode
    TCCR1B |= (1 << WGM12);

    // Set 256 prescaler
    TCCR1B |= (1 << CS12);

    // Enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
}

// Timer 1 compare interrupt service routine
ISR(TIMER1_COMPA_vect) {
    digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1);
}

void setup() {
    pinMode(LED_PIN, OUTPUT);

    // First disable all interrupts
    noInterrupts();

    // Setup timer 1
    init_timer1();

    // Enable all interrupts
    interrupts();
}

void loop() {
    
}