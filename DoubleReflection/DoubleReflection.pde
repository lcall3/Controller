import peasy.PeasyCam;

PeasyCam cam;
final int GROUND_SIZE = 1000;
public void settings() {
    size(800, 600, P3D);
}

public void setup() {
    cam = new PeasyCam(this, 1000);
}

public void draw() {
    // Set up scene
    background(125, 175, 255);
    lights();
    scale(10);
    
    // Draw scene
    drawGround();
    
    
}

public void drawGround() {
    rectMode(CENTER);
    rect(0, 0, GROUND_SIZE, GROUND_SIZE);
}

public void drawScreen() {
    pushMatrix();
    rotateX(90);
    
    popMatrix();
}