import processing.serial.*;

Serial arduino;
int receivedValue;
IntList receivedValues;

float norm_height = 200;
float center_height;
float norm_width;

final int PULSE_PER_REV = 96;
final float DESTINATION = 30;

void setup() {
    size(800, 600);
    try {
        String portName = Serial.list()[0];
        arduino = new Serial(this, portName, 9600);
    } catch (Throwable t) {
    }

    frameRate(60);

    center_height = height / 2 + 100;
    norm_width = width - 50;

    receivedValues = new IntList();
}

void draw() {
    background(0);
    drawUI();
    drawExpected();
    drawSerialResponse();
}

void drawUI() {
    stroke(255);
    line(50, 0, 50, height);
    line(0, center_height, width, center_height);
    fill(255);
    text("time (s)", width - textWidth("time (s)"), center_height - 4);
    text("response (deg)", 54, 20);
}

void drawExpected() {
    stroke(255, 255, 0);
    line(50, center_height - norm_height, width, center_height - norm_height);
    fill(255, 255, 0);
    text("Expected response", 54, center_height - norm_height - 4);
    text(str(DESTINATION), 0, center_height - norm_height - 4);
}

void drawSerialResponse() {
    if (arduino != null & arduino.available() > 0) {
        String readString = arduino.readStringUntil(10);
        if (readString == null) return;
        receivedValue = Integer.parseInt(readString.trim());
        receivedValues.append(receivedValue);
    }
    
    // Draw the line
    int dataPoints = receivedValues.size();
    if (dataPoints == 0) return;

    float delta_x = norm_width / dataPoints;
    strokeWeight(3);
    stroke(0, 255, 0);
    for (int i = 1; i < dataPoints; i++) {
        int sensor = receivedValues.get(i);
        float angle = sensor * 360.0 / PULSE_PER_REV;
        float y = map(angle, 0, DESTINATION, center_height, center_height - norm_height);
        float prev_y = map(receivedValues.get(i - 1) * 360.0 / PULSE_PER_REV, 0, DESTINATION, center_height, center_height - norm_height);
        line(50 + (i - 1) * delta_x, prev_y, 50 + i * delta_x, y);
    }
    strokeWeight(1);
}