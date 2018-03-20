// lcall3 Controller is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// lcall3 Controller is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with lcall3 Controller. If not, see <http://www.gnu.org/licenses/>.

import garciadelcastillo.dashedlines.*;
DashedLines dash;

int left, right, top, bottom;

// Output to file
final String shapeName = "shape";
boolean useDouble = false;
PrintWriter output;

// The rise time for the controller end-to-end in milliseconds
final float timeFactor = 100.0;
final float minTimeFactor = 0.3;
final float maxTimeFactor = 2.0;

ArrayList<PVector> verts = new ArrayList<PVector>();
FloatList vertsTime = new FloatList();

// Laser simulation
final float ACCEL_K = 0.15;
final float ACCEL_LIMIT = 0.08;
final float VEL_B = 0.5;
final float FRATE = 1.0;
final boolean DRAW_LINES = true;
final int REFRESH_OPACITY = 30;
PVector position;
PVector position_prev;
PVector velocity;
PVector acceleration;
PGraphics screen;

void setup() {
    size(1280, 800);
    
    left = width/2 - 300;
    right = left + 600;
    top = height/2 - 300;
    bottom = top + 600;
    
    dash = new DashedLines(this);
    dash.pattern(5);
    
    position = new PVector(0, 0);
    position_prev = new PVector(0, 0);
    velocity = new PVector(0, 0);
    acceleration = new PVector(0, 0);
    
    screen = createGraphics(600, 600);
    frameRate(60);
}

void draw() {
    background(0);
    image(screen, left, top);
    drawCanvas();
    drawCursor();
    drawVertList();
    drawTrail();
    drawTracer();
    drawInstructions();
}

void drawCanvas() {
    rectMode(CENTER);
    noFill();
    stroke(150);
    strokeWeight(1);
    rect(width/2, height/2, 600, 600);
    line(left+300, top, left+300, bottom);
    line(left, top+300, right, top+300);
    ellipse(width/2, height/2, 300, 300);
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
            
            // Get time vector to starting vertex
            distance = verts.get(verts.size() - 1).dist(verts.get(0));
            time = map(distance, 0, 2, minTimeFactor * timeFactor, maxTimeFactor * timeFactor);
            vertsTime.set(0, time);
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
    if (verts.size() > 1) {
        for (int i = 1, l = verts.size(); i < l; i++) {
            PVector current = toScreenCoords(verts.get(i));
            PVector prev = toScreenCoords(verts.get(i - 1));
            
            stroke(255, 0, 0);
            ellipse(current.x, current.y, 5, 5);
            stroke(
                map(i, 0, l, 0, 5),
                map(i, 0, l, 242, 117),
                map(i, 0, l, 96, 230),
                80
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
        stroke(255, 0, 0);
        ellipse(current.x, current.y, 5, 5);
    }
}

void writeShape() {
    output.println("// THIS IS AN AUTO GENERATED FILE. DO NOT EDIT!");
    output.println("#ifdef " + shapeName.toUpperCase() + "_H");
    output.println("#define " + shapeName.toUpperCase() + "_H");
    output.println("#define N_VERTICES " + str(verts.size()));
    output.println("const " + (useDouble ? "double" : "float") + " _vx[N_VERTICES] = {");
    for (int i = 0, l = verts.size(); i < l; i++) {
        PVector v = verts.get(i);
        output.println("    " + str(v.x) + (i == l-1 ? "" : ","));
    }
    output.println("};");
    output.println("const " + (useDouble ? "double" : "float") + " _vy[N_VERTICES] = {");
    for (int i = 0, l = verts.size(); i < l; i++) {
        PVector v = verts.get(i);
        output.println("    " + str(v.y) + (i == l-1 ? "" : ","));
    }
    output.println("};");
    output.println("const " + "unsigned short" + " _time_vector[N_VERTICES] = {");
    for (int i = 0, l = vertsTime.size(); i < l; i++) {
        int time = int(vertsTime.get(i));
        output.println("    " + str(time) + (i == l-1 ? "" : ","));
    }
    output.println("};");
    output.println("#endif");
}

void drawInstructions() {
    textSize(20);
    fill(255);
    text("ShapeMaker", 100, top);
    textSize(12);
    text("Click anywhere in the canvas to", 100, top + 14);
    text("add vertices.", 100, top + 28);

    text("The vertices are in sequential order.", 100, top + 56);
    text("Press BACKSPACE to delete last vertex.", 100, top + 84);
    text("Press SHIFT+S to save to file", 100, top + 112);
}
int currentVert = 0;
int millis_prev;

void drawTracer() {
    if (verts.size() < 1) return;
    
    try {
        PVector nowL = verts.get(currentVert);
        PVector now = toScreenCoords(nowL);
        stroke(0, 255, 0);
        ellipse(now.x, now.y, 8, 8);
        
        // Update laser position
        acceleration = nowL.copy().sub(position).mult(ACCEL_K).limit(ACCEL_LIMIT);
        velocity.mult(VEL_B);
        velocity.add(acceleration);
        position_prev = position.copy();
        position.add(velocity);
        
        // Draw laser
        PVector posS = toScreenCoords(position);
        PVector posSp = toScreenCoords(position_prev);
        screen.beginDraw();
        screen.noStroke();
        screen.fill(0, REFRESH_OPACITY);
        screen.rect(0, 0, 600, 600);
        
        if (DRAW_LINES) {
            screen.stroke(255, 0, 0);
            screen.strokeWeight(8);
            screen.line(posS.x - left, posS.y - top, posSp.x - left, posSp.y - top);
            screen.stroke(255);
            screen.strokeWeight(3);
            screen.line(posS.x - left, posS.y - top, posSp.x - left, posSp.y - top);
        } else {
            screen.fill(255, 0, 0);
            screen.ellipse(posS.x - left, posS.y - top, 8, 8);
            screen.fill(255);
            screen.ellipse(posS.x - left, posS.y - top, 5, 5);
        }
        screen.endDraw();
    } catch (IndexOutOfBoundsException e) {
        println("Deletion happened at wrong time");
        currentVert = 0;
        return;
    }
    
    if ((millis() - millis_prev) * FRATE > vertsTime.get(currentVert)) {
        millis_prev = millis();
        if (currentVert == verts.size() - 1) {
            currentVert = 0;
        } else {
            currentVert++;
        }
    }
}