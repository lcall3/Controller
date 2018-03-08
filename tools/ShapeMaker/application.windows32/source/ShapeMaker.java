import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import garciadelcastillo.dashedlines.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class ShapeMaker extends PApplet {

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


DashedLines dash;

int left, right, top, bottom;

// Output to file
final String shapeName = "newShape";
boolean useDouble = false;
PrintWriter output;

// The rise time for the controller end-to-end in milliseconds
final float timeFactor = 100.0f;
final float minTimeFactor = 0.3f;
final float maxTimeFactor = 2.0f;

ArrayList<PVector> verts = new ArrayList<PVector>();
FloatList vertsTime = new FloatList();

// Laser simulation
final float ACCEL_K = 0.15f;
final float ACCEL_LIMIT = 0.08f;
final float VEL_B = 0.5f;
final float FRATE = 1.0f;
PVector position = new PVector(0, 0);
PVector velocity = new PVector(0, 0);
PVector acceleration = new PVector(0, 0);
PGraphics screen;

public void setup() {
    
    
    left = width/2 - 300;
    right = left + 600;
    top = height/2 - 300;
    bottom = top + 600;
    
    dash = new DashedLines(this);
    dash.pattern(5);
    
    screen = createGraphics(600, 600);
    frameRate(60);
}

public void draw() {
    background(0);
    image(screen, left, top);
    drawCanvas();
    drawCursor();
    drawVertList();
    drawTrail();
    drawTracer();
    drawInstructions();
}

public void drawCanvas() {
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

public void drawCursor() {
    if (mouseInCanvas()) {
        noFill();
        strokeWeight(5);
        stroke(255, 0, 0);
        point(mouseX, mouseY);
    }
}

public boolean mouseInCanvas() {
    return (mouseX >= left && mouseX <= right && mouseY >= top && mouseY <= bottom);
}

public void mouseClicked() {
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

public void keyPressed() {
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

public PVector toLaserCoords(PVector mouse) {
    PVector laser = mouse.copy();
    laser.x = map(mouse.x, left, right, -1, 1);
    laser.y = map(mouse.y, top, bottom, 1, -1);
    return laser;
}

public PVector toScreenCoords(PVector laser) {
    PVector screen = laser.copy();
    screen.x = map(laser.x, -1, 1, left, right);
    screen.y = map(laser.y, 1, -1, top, bottom);
    return screen;
}

public void drawVertList() {
    int x = right + 50;
    text("Vertices", x, top);
    textSize(12);
    for (int i = 0; i < verts.size(); i++) {
        PVector v = verts.get(i);
        text("(" + nf(v.x, 1, 4) + ", " + nf(v.y, 1, 4) + "):\t\t" + str(PApplet.parseInt(vertsTime.get(i))) + "ms", x, top + (i + 1) * 14);
    }
}

public void drawTrail() {
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
        stroke(255, 0, 0);
        ellipse(current.x, current.y, 5, 5);
    }
}

public void writeShape() {
    output.println("// THIS IS AN AUTO GENERATED FILE. DO NOT EDIT!");
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
        int time = PApplet.parseInt(vertsTime.get(i));
        output.println("    " + str(time) + (i == l-1 ? "" : ","));
    }
    output.println("};");
    output.println("#endif");
}

public void drawInstructions() {
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

public void drawTracer() {
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
        position.add(velocity);
        
        // Draw laser
        PVector posS = toScreenCoords(position);
        screen.beginDraw();
        screen.noStroke();
        screen.fill(0, 30);
        screen.rect(0, 0, 600, 600);
        screen.fill(255, 0, 0);
        screen.ellipse(posS.x - left, posS.y - top, 8, 8);
        screen.fill(255);
        screen.ellipse(posS.x - left, posS.y - top, 5, 5);
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
    public void settings() {  size(1280, 800); }
    static public void main(String[] passedArgs) {
        String[] appletArgs = new String[] { "--present", "--window-color=#666666", "--stop-color=#cccccc", "ShapeMaker" };
        if (passedArgs != null) {
          PApplet.main(concat(appletArgs, passedArgs));
        } else {
          PApplet.main(appletArgs);
        }
    }
}
