int left, right, top, bottom;

// The rise time for the controller end-to-end in milliseconds
final float timeFactor = 100.0;
final float minTimeFactor = 0.3;
final float maxTimeFactor = 2.0;

ArrayList<PVector> verts = new ArrayList<PVector>();
FloatList vertsTime = new FloatList();

void setup() {
    size(1280, 800);
    
    left = width/2 - 300;
    right = left + 600;
    top = height/2 - 300;
    bottom = top + 600;
}

void draw() {
    background(0);
    drawCanvas();
    drawCursor();
    drawVertList();
    drawTrail();
}

void drawCanvas() {
    rectMode(CENTER);
    noFill();
    stroke(150);
    strokeWeight(1);
    rect(width/2, height/2, 600, 600);
    line(left+300, top, left+300, bottom);
    line(left, top+300, right, top+300);
    fill(255);
    textSize(20);
    text("Canvas", left, top);
}

void drawCursor() {
    if (mouseInCanvas()) {
        noFill();
        strokeWeight(5);
        stroke(255, 0, 0);
        point(mouseX, mouseY);
    }
}

boolean mouseInCanvas() {
    return (mouseX >= left && mouseX <= right && mouseY >= top && mouseY <= bottom);
}

void mouseClicked() {
    if (mouseInCanvas()) {
        
        // Add point to list
        //verts.add(new PVector(
        //    map(mouseX, left, right, -1, 1),
        //    map(mouseY, top, bottom, 1, -1)
        //));
        verts.add(toLaserCoords(new PVector(mouseX, mouseY)));
        
        // Calculate the required time based on a time factor and distance
        if (verts.size() > 1) {
            float distance = verts.get(verts.size() - 1).dist(verts.get(verts.size() - 2));
            float time = map(distance, 0, 2, minTimeFactor * timeFactor, maxTimeFactor * timeFactor);
            vertsTime.append(time);
        } else {
            float time = map(verts.get(0).mag(), 0, 2, minTimeFactor * timeFactor, maxTimeFactor * timeFactor);
            vertsTime.append(time);
        }
    }
}

PVector toLaserCoords(PVector mouse) {
    PVector laser = mouse.copy();
    laser.x = map(mouse.x, left, right, -1, 1);
    laser.y = map(mouse.y, top, bottom, 1, -1);
    return laser;
}

void drawVertList() {
    int x = right + 50;
    text("Vertices", x, top);
    textSize(12);
    for (int i = 0; i < verts.size(); i++) {
        PVector v = verts.get(i);
        text("(" + nf(v.x, 1, 4) + ", " + nf(v.y, 1, 4) + "):\t\t" + str(int(vertsTime.get(i))) + "ms", x, top + (i + 1) * 14);
    }
}

void drawTrail() {
    strokeWeight(2);
    stroke(255, 255, 0);
    if (verts.size() > 1) {
        for (int i = 1, l = verts.size(); i < l; i++) {
            PVector current = verts.get(i);
            PVector prev = verts.get(i - 1);
            
            ellipse(current.x, current.y, 5, 5);
            stroke(
                map(i, 0, l, 0, 255),
                map(i, 0, l, 255, 0),
                map(i, 0, l, 0, 255)
            );
            line(
                prev.x, 
                prev.y,
                current.x,
                current.y
            );
        }
    } else if (verts.size() == 1){
        PVector current = verts.get(0);
        ellipse(current.x, current.y, 5, 5);
    }
}