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

// Socket client
var socket;

// Hack for working around not immediately sending the command
function socketEmit(cmd, data) {
    if (data === undefined) {
        socket.emit(cmd);
    } else {
        socket.emit(cmd, data);
    }
    socket.emit('nop');
}

// Flags
var isMobile = false;
var toggleMobileEmit = false;
var drawLaser = true;
var mouseDrawEnabled = false;

// detect mobile rotation
var angle_alpha = 0;
var angle_beta = 0;
var angle_gamma = 0;
var relative_alpha = 0;
var relative_beta = 0;
var relative_gamma = 0;

// Vertex array
var vertices = [];
var timeVector = [];

// Screen canvas and laser preview
var cursorX = 0;
var cursorY = 0;
var boundSize = 600;

// Physics enabled laser simulation variables
/* TODO: */
const timeFactor = 100;
const minTimeRatio = 0.2;
const maxTimeRatio = 2.0;

// Laser simulation preview
var laserScreen;
var position;
var position_prev;
var velocity;
var accel;
const accel_k = 0.15;
const accel_lim = 0.09;
const vel_decay = 0.4;

// Sound
var sfx_connected;
var sfx_focus;

// Mobile UI components
var btns = [];
const btns_def_list = [
    ['Push', setVertexEvent],
    ['Pop', removeVertexEvent],
    ['Go', masterGoEvent],
    ['Toggle Control', toggleControlEvent],
    ['Origin', zeroToOriginEvent]
];

// Helping objs
var space;
var cereal;

// p5 functions
function setup() {
    canvas = createCanvas(windowWidth, windowHeight, P2D);
    canvas.position(0, 0);
    background(0);

    // Simulate preview setups
    laserScreen   = createGraphics(boundSize, boundSize);
    position      = createVector(0, 0);
    position_prev = createVector(0, 0);
    velocity      = createVector(0, 0);
    accel         = createVector(0, 0);

    var x_start = 10;
    var y_start = 40;
    var y_incre = 65;
    for (var i = 0; i < btns_def_list.length; i++) {
        var btn_def = btns_def_list[i];
        btns.push(new Button(10, 40 + i * y_incre, btn_def[0], btn_def[1]));
    }

    // Sound
    soundFormats('mp3', 'ogg');
    sfx_connected = loadSound('assets/connect.ogg');
    sfx_focus = loadSound('assets/focus.ogg');

    // Space conversion
    space = new Space(boundSize);

    // Serial communication with Controller
    cereal = new Cereal();
}

function draw() {
    background(0);
    drawCopyright('beta v0.7');

    if (isMobile) {
        drawMobileUI();
    } else {
        drawHostUI();
    }
}


// Universal draw functions
function drawCopyright(version) {
    fill(255);
    textAlign(LEFT, BASELINE);
    textSize(10);
    text('lcall3 Controller ' + version, 20, 20);
    text('Copyright 2018 (c) Muchen He', 20, 32);
}

function playTone() {
    sfx_connected.play();
}

// ======== MOBILE DRAWING FUNCTIONS ========
function drawMobileUI() {
    // Draw gyro control indicator
    drawGyroControlIndicator(toggleMobileEmit);

    // Draw live control indictator
    // TODO:

    // Draw buttons
    for (var i = 0, n = btns.length; i < n; i++) {
        btns[i].draw();
    }
}

function drawGyroControlIndicator(active) {
    if (active) {
        fill(255, 0, 0);
    } else {
        fill(255);
    }
    rect(0, height - 20, width, height);
}

// ======== HOST DRAWING FUNCTIONS ======
function drawHostUI() {
    rectMode(CENTER);
    noFill();

    push();
    translate(width/2, height/2);

    // Draw tracer graphics
    image(laserScreen, -boundSize/2, -boundSize/2);

    stroke(100);
    rect(0, 0, boundSize, boundSize);
    line(0, boundSize/2, 0, -boundSize/2);
    line(boundSize/2, 0, -boundSize/2, 0);

    angleMode(DEGREES);

    // Compute inverse kinematic
    var d = 1000;
    var a = -(angle_alpha - relative_alpha);
    var b = -(angle_beta - relative_beta);
    cursorX = d * tan(a);
    cursorY = d * tan(b);

    // Draw laser dot
    drawCursor();

    // Draw saved vertices
    drawVertices();

    pop();

    // Draw vertex UI
    drawVertexList();

    // Draw serial status UI
    drawHostSerialStatusUI();

    // Update drawing of tracer
    drawTracer();
}

function drawCursor() {
    // stroke(255);
    // line(cursorX - 10, cursorY, cursorX + 10, cursorY);
    // line(cursorX, cursorY - 10, cursorX, cursorY + 10);

    fill('#F00');
    ellipse(cursorX, cursorY, 14, 14);
    fill(255);
    ellipse(cursorX, cursorY, 5, 5);
}

function drawVertices() {
    noFill();
    stroke(150);
    for (var i = 0; i < vertices.length; i++) {
        var vec = space.normToScreen(vertices[i]);
        var vecNext;
        if (i == vertices.length - 1) {
            vecNext = space.normToScreen(vertices[0]);
        } else {
            vecNext = space.normToScreen(vertices[i + 1]);
        }

        // Draw shape made by the vertex
        line(vec.x, vec.y, vecNext.x, vecNext.y);
        ellipse(vec.x, vec.y, 10, 10);
    }
}

function drawVertexList() {
    var x = 20;
    var y = 50;
    textSize(12);
    fill(255);
    for (var i = 0; i < vertices.length; i++) {
        var vec = vertices[i];
        text(
            '(' + vec.x + ', ' + vec.y + '):' + timeVector[i] + 'ms',
            x,
            y + i * 14
        );
    }
}

function drawHostSerialStatusUI() {
    noStroke();
    textAlign(CENTER, CENTER);
    textSize(16);
    if (cereal.connectedPort === undefined) {
        fill('F88');
        text('Serial offline', width / 2, 30);
    } else {
        fill('8F8');
        text('Connected to ' + cereal.connectedPort, width / 2, 30);
    }
}

var vertex_i = 0;
var millis_prev = 0;
function drawTracer() {
    if (vertices.length < 1) return;

    try {
        var nowL = vertices[vertex_i];
        var now = space.normToScreen(nowL);

        // Update simulated kinematics
        accel = nowL.copy().sub(position).mult(accel_k).limit(accel_lim);
        velocity.mult(vel_decay);
        velocity.add(accel);
        position_prev = position.copy();
        position.add(velocity);

        // Draw laser
        var posS = space.normToScreen(position);
        var posSp = space.normToScreen(position_prev);
        laserScreen.push();
        laserScreen.scale(0.5); // HACK: for some reason it is doubled
        laserScreen.fill(0,80);
        laserScreen.noStroke();
        laserScreen.rect(0, 0, boundSize, boundSize);
        laserScreen.translate(boundSize/2, boundSize/2);
        laserScreen.stroke('#f00');
        laserScreen.strokeWeight(8);
        laserScreen.line(posS.x, posS.y, posSp.x, posSp.y);
        laserScreen.stroke('#F88');
        laserScreen.strokeWeight(3);
        laserScreen.line(posS.x, posS.y, posSp.x, posSp.y);
        laserScreen.pop();
    } catch (e) {
        console.warn(e);
        vertex_i = 0;
        return;
    }

    // Update index based on time
    if ((millis() - millis_prev) > timeVector[vertex_i]) {
        millis_prev = millis();
        vertex_i = (vertex_i === vertices.length - 1) ? 0 : vertex_i + 1;
    }
}

function resetOrigin() {
    relative_alpha = angle_alpha;
    relative_beta = angle_beta;
    relative_gamma = angle_gamma;
}

// UI handler functions (sending from mobile)
function setVertexEvent() {
    socketEmit('setVertex');
}
function removeVertexEvent() {
    socketEmit('removeVertex');
}
function masterGoEvent() {
    socketEmit('masterGo');
}
function toggleControlEvent() {
    toggleMobileEmit = !toggleMobileEmit;
}
function zeroToOriginEvent() {
    socketEmit('zeroToOrigin');
}

// Socket handler functions (receive from mobile -> server)
function onPushVertex() {

    // Add vertex
    vertices.push(space.screenToNorm(createVector(cursorX, cursorY)));
    var n = vertices.length;
    console.log('Vertex added: ', vertices[n - 1].x, vertices[n - 1].y);

    // Update time vector
    if (n > 1) {
        var normDistTo = vertices[n - 1].dist(vertices[n - 2]);
        var timeTo = map(normDistTo, 0, 2, minTimeRatio * timeFactor, maxTimeRatio * timeFactor);
        timeVector.push(parseInt(timeTo));

        // Update the time vector to starting index
        normDistTo = vertices[n - 1].dist(vertices[0]);
        timeTo = map(normDistTo, 0, 2, minTimeRatio * timeFactor, maxTimeRatio * timeFactor);
        timeVector[0] = parseInt(timeTo);
    } else {
        var timeTo = map(vertices[0].mag(), 0, 2, minTimeRatio * timeFactor, maxTimeRatio * timeFactor);
        timeVector.push(parseInt(timeTo));
    }

    sfx_focus.play();
}
function onPopVertex() {
    var n = vertices.length;
    if (n > 0) {
        vertices.pop();
        timeVector.pop();
    }
}
function onMasterProceed() {
    cereal.sendVerticesToController(vertices, timeVector, space);
}

// Socket functions
// Setup socket, this function is called by the html js
function setupSocket(addr, port) {
    var url = 'http://' + addr + ':' + port;
    socket = io.connect(url);
    console.log('Connecting to ' + url);

    // Bind signals to slot
    socket.on('deviceOrientationChanged', function(data) {
        angle_alpha = data.alpha;
        angle_beta = data.beta;
        angle_gamma = data.gamma;
    });

    socket.on('pushVertex', onPushVertex);
    socket.on('popVertex', onPopVertex);
    socket.on('masterProceed', onMasterProceed);
    socket.on('resetOrigin', resetOrigin);

    socket.on('newMaster', playTone);
}

// Mobile specific orientation event listener
function setupDeviceOrientation() {
    // Device orientation event
    if (window.DeviceOrientationEvent) {
        window.addEventListener('deviceorientation', onOrientationChange);
    }
    isMobile = true;
}

// Handlers
function onOrientationChange(e) {
    if (toggleMobileEmit) {
        data = {
            alpha: e.alpha,
            beta: e.beta,
            gamma: e.gamma
        };
        socketEmit('deviceOrientationChange', data);
    }
}

// User interfacing
function keyPressed() {
    if (!isMobile) {
        if (keyCode === 32) {   // space bar
            resetOrigin();
        } else if (keyCode === 67) {    // 'c': connect
            if (cereal !== undefined) {
                cereal.listAgain();
            }
        } else if (keyCode === 83) {  // 's': save vertices and go
            if (cereal !== undefined) {
                cereal.sendVerticesToController(vertices, timeVector, space);
            }
        } else if (keyCode === 8) { // backspace
            onPopVertex();
        }
    }
}

function mouseClicked() {
    if (mouseDrawEnabled) {
        cursorX = mouseX - width / 2;
        cursorY = mouseY - height / 2;
        onPushVertex();
    }
}

// Mobile interfacing
function deviceShaken() {
    // Request a mobile controller
    socket.emit('requestToBeMaster');
    socket.on('requestToBeMasterResponse', function(approve) {
        if (approve) {
            setupDeviceOrientation();
        }
    });
}

function touchStarted() {
    // Check that where we are pressing is inside the button or not
    if (isMobile) {
        for (var i = 0, n = btns.length; i < n; i++) {
            if (btns[i].isMouseInside(mouseX, mouseY)) {
                btns[i].callHandler();
            }
        }
    }
}

function serialSelectPort(port) {
    cereal.commence(port);
}