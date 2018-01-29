import processing.serial.*;

Serial arduino;
int receivedValue;
IntList receivedValues;

float norm_height = 200;
float center_height;
float norm_width;

final int PULSE_PER_REV = 96;
final float DESTINATION = 360;

final int BAUD_RATE = 9600;

void setup() {
    size(800, 600);

    String[] portList = Serial.list();
    for (int i = 0; i < portList.length; i++) {
        try {
            String portName = Serial.list()[i];
            arduino = new Serial(this, portName, BAUD_RATE);
            break;
        } catch (Throwable t) {
            println(Serial.list()[i] + " is not available for Serial communication");
        }
    }

    frameRate(60);

    center_height = height / 2 + 100;
    norm_width = width - 50;

    receivedValues = new IntList();
}

void draw() {
    background(0);
    drawUI();

    if (arduino != null) {
        drawExpected();
        drawSerialResponse();
    } else {
        drawNA();
    }
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
    text("Expected response (" + str(DESTINATION) + ")", 54, center_height - norm_height - 4);
}

void drawSerialResponse() {
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

final int LF = 10;
void serialEvent(Serial p) {
    if (p != null & p.available() > 0) {
        String readString = p.readStringUntil(LF);

        if (readString == null) {
            return;
        } else if (readString.equals("###")) {
            receivedValues.clear();
        } else {
            receivedValue = Integer.parseInt(readString.trim());
            if (receivedValues.size() > 3000) {
                receivedValues.clear();
            }
            receivedValues.append(receivedValue);
        }
    }
}

void drawNA() {
    stroke(255, 0, 0);
    line(0, 0, width, height);
    line(0, height, width, 0);
}