
// Socket client
var socket;

var isMobile = false;
var toggleMobileEmit = false;

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

    socket = io.connect('http://192.168.0.101:8000');

    // Socket incoming message handling
    socket.on('mouseDraggedEvent', onMouseDraggedEvent);
    socket.on('rotateEvent', onRotateEvent);

    // graphics setup
    background(0);
}

function setupDeviceOrientation() {
    // Device orientation event
    if (window.DeviceOrientationEvent) {
        window.addEventListener('deviceorientation', onOrientationChange);
    }
    isMobile = true;
}

function mouseDragged() {
    fill(50, 255, 50);
    ellipse(mouseX, mouseY, 20, 20);
    fill(255);
    ellipse(mouseX, mouseY, 10, 10);

    // Prepare payload to be sent
    var data = {
        x: mouseX,
        y: mouseY
    };

    // Send load
    socket.emit('mouseDragged', data);
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

function onMouseDraggedEvent(data) {
    fill(255, 50, 50);
    ellipse(data.x, data.y, 20, 20);
    fill(255);
    ellipse(data.x, data.y, 10, 10);
}

function onOrientationChange(e) {
    if (toggleMobileEmit) {
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