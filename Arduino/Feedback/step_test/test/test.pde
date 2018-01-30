void setup() {
    size(500, 500);
}

float x;
void draw() {
    background(0);
    ellipse(x, height / 2, 50, 50);
    
    float vx = (mouseX - x) * 0.05;
    x += vx;
}