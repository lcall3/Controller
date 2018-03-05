import garciadelcastillo.dashedlines.*;
DashedLines dash;

int left, right, top, bottom;

// Output to file
final String shapeName = "newShape";
boolean useDouble = false;
PrintWriter output;

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
    
    dash = new DashedLines(this);
    dash.pattern(5);
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

void keyPressed() {
    if (key == BACKSPACE) {
        // Remove the last entry in the list
        if (verts.size() > 0) {
            verts.remove(verts.size() - 1);
            vertsTime.remove(vertsTime.size() - 1);
        }
    } else if (key == 'S') {
        // Save to file
        output = createWriter(shapeName + ".h");
        writeShape();
        output.flush();
        output.close();
    }
}

PVector toLaserCoords(PVector mouse) {
    PVector laser = mouse.copy();
    laser.x = map(mouse.x, left, right, -1, 1);
    laser.y = map(mouse.y, top, bottom, 1, -1);
    return laser;
}

PVector toScreenCoords(PVector laser) {
    PVector screen = laser.copy();
    screen.x = map(laser.x, -1, 1, left, right);
    screen.y = map(laser.y, 1, -1, top, bottom);
    return screen;
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
            PVector current = toScreenCoords(verts.get(i));
            PVector prev = toScreenCoords(verts.get(i - 1));
            
            ellipse(current.x, current.y, 5, 5);
            stroke(
                map(i, 0, l, 0, 5),
                map(i, 0, l, 242, 117),
                map(i, 0, l, 96, 230)
            );
            line(prev.x, prev.y, current.x, current.y);
            
            if (i == l-1) {
                // Draw a line from end to origin to complete the loop
                PVector first = toScreenCoords(verts.get(0));
                dash.line(first.x, first.y, current.x, current.y);
            }
        }
        
    } else if (verts.size() == 1){
        PVector current = toScreenCoords(verts.get(0));
        ellipse(current.x, current.y, 5, 5);
    }
}

void writeShape() {
    output.println("#ifdef " + shapeName.toUpperCase() + "_H");
    output.println("#define " + shapeName.toUpperCase() + "_H");
    output.println("#define N_VERTICES " + str(verts.size()));
    output.println("const " + (useDouble ? "double" : "float") + " vertices_x[N_VERTICES] = {");
    for (int i = 0, l = verts.size(); i < l; i++) {
        PVector v = verts.get(i);
        output.println("    " + str(v.x) + (i == l-1 ? "" : ","));
    }
    output.println("};");
    output.println("const " + (useDouble ? "double" : "float") + " vertices_y[N_VERTICES] = {");
    for (int i = 0, l = verts.size(); i < l; i++) {
        PVector v = verts.get(i);
        output.println("    " + str(v.y) + (i == l-1 ? "" : ","));
    }
    output.println("};");
    output.println("const " + "unsigned short" + " time_vector[N_VERTICES] = {");
    for (int i = 0, l = vertsTime.size(); i < l; i++) {
        int time = int(vertsTime.get(i));
        output.println("    " + str(time) + (i == l-1 ? "" : ","));
    }
    output.println("};");
    output.println("#endif");
}