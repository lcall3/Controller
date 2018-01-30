import processing.serial.*;

Serial serialPort;
int lf = 10;

int countPerRev = 96;

void setup() {
    size(300, 300);
    
    serialPort = new Serial(this, "COM3", 9600);

    noFill();
    strokeWeight(5);
}

String receivedVal;
float encoderPos = 0;
float encoderPos_tgt = 0;
float angle;

void draw() {
    background(255);
    
    if (serialPort != null && serialPort.available() > 0) {
        receivedVal = serialPort.readStringUntil(lf);
        if (receivedVal != null) {
            print(receivedVal);
            encoderPos_tgt = float(receivedVal);
            if (encoderPos_tgt == Float.NaN) {
                encoderPos_tgt = 0.0;
            }
        }
    }
    
    //encoderPos = lerp(encoderPos, encoderPos_tgt, 0.1);
    encoderPos = encoderPos_tgt;
    angle = -(encoderPos * TWO_PI / countPerRev);
    
    ellipseMode(CENTER);
    ellipse(width / 2, height / 2, 250, 250);
    
    ellipse(100 * cos(-angle) + width / 2, 100 * sin(-angle) + height / 2, 10, 10);
}