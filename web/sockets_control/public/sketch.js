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
    ['Push', setVertexEvent],
    ['Pop', removeVertexEvent],
    ['Go', masterGoEvent],
    ['Toggle Control', toggleControlEvent],
    ['Origin', zeroToOriginEvent]
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
    text('beta v0.5 Copyright 2018 (c) Muchen He', 20, 20);
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


var cursorX = 0;
var cursorY = 0;
var boundSize = 600;
function drawHostUI() {
    rectMode(CENTER);
    noFill();

    push();
    translate(width/2, height/2);
    stroke(100);
    rect(0, 0, boundSize, boundSize);
    line(0, boundSize/2, 0, -boundSize/2);
    line(boundSize/2, 0, -boundSize/2, 0);
    noStroke();

    angleMode(DEGREES);

    // Compute inverse kinematic
    var d = 1000;
    var a = -(angle_alpha - relative_alpha);
    var b = -(angle_beta - relative_beta);
    cursorX = d * tan(a);
    cursorY = d * tan(b);

    // Draw laser dot
    fill('#0F0');
    ellipse(cursorX, cursorY, 10, 10);
    fill(250);
    ellipse(cursorX, cursorY, 5, 5);
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

}
function onPopVertex() {

}
function onMasterGo() {

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
    socket.on('masterGo', onMasterGo);
    socket.on('resetOrigin', resetOrigin);
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
        } else if (keyCode === 68) {    // 'D'
            if (connectedSerial !== '') {
                serial.close();
                console.log('Serial port closed');
                connectedSerial = '';
            }
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
    if (isMobile) {
        for (var i = 0, n = btns.length; i < n; i++) {
            if (btns[i].isMouseInside(mouseX, mouseY)) {
                btns[i].callHandler();
            }
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
        
        if (list.length !== 0) {
            console.log('Available serial port list updated:');
            if (listSerialPorts !== undefined) listSerialPorts(list);
        } else {
            alert('No serial port available');
        }
    });

    serial.on('error', function(e) {
        console.error(e);
    })

    serial.on('data', SerialEvent);
}

function serialSelectPort(port) {
    serial.open(port, { baudRate: 115200 }, function() {
        console.log('Serial port opened at ' + port);
    });
    hideSerialPorts();
    connectedSerial = port;
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