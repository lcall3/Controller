
// Socket client
var socket;

// Flags
var isMobile = false;
var toggleMobileEmit = false;
var socketSetup = false;
var drawLaser = true;

// detect mobile rotation
var angle_alpha = 0;
var angle_beta = 0;
var angle_gamma = 0;
var relative_alpha = 0;
var relative_beta = 0;
var relative_gamma = 0;

function setup() {
    canvas = createCanvas(windowWidth, windowHeight, WEBGL);
    canvas.position(0, 0);

    // graphics setup
    background(0);
}

function setupSocket(addr, port) {
    var url = 'http://' + addr + ':' + port;
    socket = io.connect(url);
    console.log('Connecting to ' + url);

    // Socket incoming message handling
    socket.on('rotateEvent', onRotateEvent);
    socketSetup = true;
}

function setupDeviceOrientation() {
    // Device orientation event
    if (window.DeviceOrientationEvent) {
        window.addEventListener('deviceorientation', onOrientationChange);
    }
    isMobile = true;
}

// Shake to enable gyro emit
function deviceShaken() {
    setupDeviceOrientation();
}

function draw() {
    background(0);

    if (isMobile) {
        if (toggleMobileEmit) {
            fill(255, 0, 0);
        } else {
            fill(150);
        }
        ellipse(0, 0, 100, 100);
    } else {

        if (drawLaser) {
            // Draw grid
            rectMode(CENTER);
            noFill();
            stroke(255);
            rect(0, 0, 600, 600);
            line(0, 300, 0, -300);
            line(300, 0, -300, 0);
            noStroke();

            var k = -500;
            var l = 0.5;

            angleMode(DEGREES);
            var a = (angle_alpha - relative_alpha) / l;
            var b = (angle_beta - relative_beta) / l;

            var x = k * tan(a);
            var y = k * tan(b);
            fill(255, 0, 0);
            ellipse(x, y, 10, 10);
            fill(250);
            ellipse(x, y, 5, 5);
        } else {
            fill(255);
            angleMode(DEGREES);
            push();
            rotateX(angle_beta - relative_beta);
            rotateY(angle_alpha - relative_alpha);
            rotateZ(angle_gamma - relative_gamma);
            normalMaterial();
            box(100);
            pop();
        }
    }
}

function touchStarted() {
    toggleMobileEmit = true;
}

function touchEnded() {
    toggleMobileEmit = false;
}

function keyPressed() {
    if (keyCode === 32) { // space bar
        // Recalibrate position
        relative_alpha = angle_alpha;
        relative_beta = angle_beta;
        relative_gamma = angle_gamma;
    }
}

function onOrientationChange(e) {
    if (toggleMobileEmit && socketSetup) {
        data = {
            alpha: e.alpha,
            beta: e.beta,
            gamma: e.gamma
        };
        socket.emit('deviceOrientationChange', data);
    }
}

function onRotateEvent(data) {
    if (isMobile) return;
    angle_alpha = data.alpha;
    angle_beta = data.beta;
    angle_gamma = data.gamma;
}