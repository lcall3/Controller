// Socket client
var socket;

// Hack for working around not immediately sending the command
function socketEmit(cmd, data) {
    if (data === undefined) {
        socket.emit(cmd);
    } else {
        socket.emit(cmd, data)
    }
    socket.emit('nop');
}

// Flags
var isMobile = false;
var toggleMobileEmit = false;
var drawLaser = true;

// detect mobile rotation
var angle_alpha = 0;
var angle_beta = 0;
var angle_gamma = 0;
var relative_alpha = 0;
var relative_beta = 0;
var relative_gamma = 0;


// Mobile UI components
var btns = [];
const btns_def_list = [
    ['Push', onSetVertex],
    ['Pop', onRemoveVertex],
    ['Go', onGo],
    ['Toggle Control', onToggleControl],
    ['Origin', onZeroToOrigin]
];

// p5 functions
function setup() {
    canvas = createCanvas(windowWidth, windowHeight, P2D);
    canvas.position(0, 0);
    background(0);

    var x_start = 10;
    var y_start = 40;
    var y_incre = 65;
    for (var i = 0; i < btns_def_list.length; i++) {
        var btn_def = btns_def_list[i];
        btns.push(new Button(10, 40 + i * y_incre, btn_def[0], btn_def[1]));
    }
}

function draw() {
    background(0);
    fill(255);
    textAlign(LEFT, BASELINE);
    textSize(10);
    text('beta v0.4 Copyright 2018 (c) Muchen He', 20, 20);
    if (isMobile) {
        drawMobileUI();
    } else {
        drawHostUI();
    }
}


function drawMobileUI() {
    if (toggleMobileEmit) {
        fill(255, 0, 0);
    } else {
        fill(255);
    }
    rect(0, height-20, width, height);

    // Buttons
    for (var i = 0, n = btns.length; i < n; i++) {
        btns[i].draw();
    }
}

function drawHostUI() {
    rectMode(CENTER);
    noFill();

    push();
    translate(width/2, height/2);
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
    pop();

    // Draw vertex UI

    // Draw serial status UI
    drawHostSerialStatusUI();
}


function drawHostSerialStatusUI() {
    fill(connectedSerial !== '' ? '#8F8' : '#F88');
    noStroke();
    textAlign(CENTER, CENTER);
    textSize(16);
    text(connectedSerial !== '' ? 'Serial connected to ' + connectedSerial : 'Serial offline', width / 2, 30);
}

function resetOrigin() {
    relative_alpha = angle_alpha;
    relative_beta = angle_beta;
    relative_gamma = angle_gamma;
}

// UI handler functions
function onSetVertex() {
    socketEmit('setVertex');
}
function onRemoveVertex() {
    socketEmit('removeVertex');
}
function onGo() {
    socketEmit('masterGo');
}
function onToggleControl() {
    toggleMobileEmit = !toggleMobileEmit;
}
function onZeroToOrigin() {
    socketEmit('zeroToOrigin');
}

// Socket functions
// Setup socket, this function is called by the html js
function setupSocket(addr, port) {
    var url = 'http://' + addr + ':' + port;
    socket = io.connect(url);
    console.log('Connecting to ' + url);

    socket.on('deviceOrientationChanged', function(data) {
        angle_alpha = data.alpha;
        angle_beta = data.beta;
        angle_gamma = data.gamma;
    });

    socket.on('resetOrigin', function() {
        resetOrigin();
    });
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
            relative_gamma = angle_gamma;
        } else if (keyCode === 67) {    // 'C'
            console.log('Initializing serial...');
            setupSerial();
        }
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
    for (var i = 0, n = btns.length; i < n; i++) {
        if (btns[i].isMouseInside(mouseX, mouseY)) {
            btns[i].callHandler();
        }
    }
}

// Serial interfacing
var serial;

var connectedSerial = '';

function setupSerial() {
    serial = new p5.SerialPort();

    // Bind signals
    serial.on('connected', function() {
        console.log('Serial server active; awaiting devices');
    });

    serial.on('list', function(list) {
        console.log('Available serial port list updated:');
        for (var i = 0; i < list.length; i++) {
            console.log(i + " " + list[i]);
        }
    });

    serial.on('error', function(e) {
        console.error(e);
    })

    serial.on('data', SerialEvent);
}

function SerialEvent(data) {
    if (serial.available()) {
        var c = serial.readChar();

        if (c === '$') {
            // Do something with special characters
            return;
        } else {
            console.log(c);
        }
        // serial.clear();
    }
}

class Button {
    constructor(x, y, name, handler) {
        this.x = x;
        this.y = y;
        this.name = name;
        this.width = width - 2 * this.x;
        this.height = 60;
        this.enabled = true;
        this.handler = handler;
        this.size = 20;
    }

    draw() {
        rectMode(CORNER);
        var btnColor;
        if (this.enabled) {
            if (this.isMouseInside(mouseX, mouseY) && mouseIsPressed) {
                btnColor = color('#8F8');
            } else {
                btnColor = color('#FFF');
            }
        } else {
            btnColor = color('#444');
        }
        stroke(btnColor);
        noFill();
        rect(this.x, this.y, this.width, this.height);
        fill(btnColor);
        noStroke();
        textAlign(CENTER, CENTER);
        textSize(this.size);
        text(this.name, this.x + this.width / 2, this.y + this.height / 2);
    }

    callHandler() {
        this.handler();
    }

    isMouseInside(x, y) {
        if (x > this.x && y > this.y && x < this.x + this.width && y < this.y + this.height) {
            return true;
        } else {
            return false;
        }
    }

    setEnable(enable) {
        this.enable = enable;
    }

    setXY(x, y) {
        this.x = x;
        this.y = y;
    }

    setWidth(w) {
        this.width = w;
    }

    setHeight(h) {
        this.height = h;
    }
}