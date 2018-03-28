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
var mouseDrawEnabled = true;

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

// Physics enabled laser simulation variables
/* TODO: */
const timeFactor = 100;
const minTimeRatio = 0.2;
const maxTimeRatio = 2.0;

// Screen coords to pulse coords mapping constants
const YAW_MIN = -100;
const YAW_MAX = 100;
const PITCH_MIN = -50;
const PITCH_MAX = 50;

// SCP
const SCP = {
    ARRAY_LENGTH: '#',
    START_ARRAY: '@',
    ARRAY_SEPARATE: ',',
    NEXT_ENTRY: '&',
    END_ARRAY: '!'
};

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

    // Sound
    soundFormats('mp3', 'ogg');
    sfx_connected = loadSound('assets/connect.ogg');
    sfx_focus = loadSound('assets/focus.ogg');
}

function draw() {
    background(0);
    fill(255);
    textAlign(LEFT, BASELINE);
    textSize(10);
    text('lcall3 Controller beta v0.5', 20, 20);
    text('Copyright 2018 (c) Muchen He', 20, 32);
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

function playTone() {
    sfx_connected.play();
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

    // Draw saved vertices
    drawVertices();

    pop();

    // Draw vertex UI
    drawVertexList();

    // Draw serial status UI
    drawHostSerialStatusUI();
}

function drawVertices() {
    noFill();
    stroke('#0F0');
    for (var i = 0; i < vertices.length; i++) {
        var vec = normToScreen(vertices[i]);
        var vecNext;
        if (i == vertices.length - 1) {
            vecNext = normToScreen(vertices[0]);
        } else {
            vecNext = normToScreen(vertices[i + 1]);
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

    // Add vertex
    vertices.push(screenToNorm(createVector(cursorX, cursorY)));
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
    sendVerticesToController();
    alert(vertices.length + ' vertices sent to the controller');
}

// Util functions
function screenToNorm(screenVec) {
    return createVector(
        constrain(map(screenVec.x, -boundSize/2, boundSize/2, -1, 1), -1, 1),
        constrain(map(screenVec.y, -boundSize/2, boundSize/2, -1, 1), -1, 1)
    );
}

function normToScreen(normVec) {
    return createVector(
        map(normVec.x, -1, 1, -boundSize/2, boundSize/2),
        map(normVec.y, -1, 1, -boundSize/2, boundSize/2)
    );
}

function normToPulses(normVec) {
    return createVector(
        map(normVec.x, -1, 1, YAW_MIN, YAW_MAX),
        map(normVec.y, -1, 1, PITCH_MIN, PITCH_MAX)
    );
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
        } else if (keyCode === 67) {    // 'c': connect to serial
            console.log('Initializing serial...');
            setupSerial();
        } else if (keyCode === 68) {    // 'd': disconnect from serial
            if (connectedSerial !== '') {
                serial.close();
                console.log('Serial port closed');
                connectedSerial = '';
            }
        } else if (keyCode === 83) {  // 's': save vertices and go
            sendVerticesToController();
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
        console.warn(e);
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
        console.log(connectedSerial + ': ' + c);
    }
}

function sendVerticesToController() {
    if (connectedSerial === '') return;

    // Send size of array
    sendChar(SCP.ARRAY_LENGTH);
    var n = parseInt(vertices.length).toString();
    for (var ni = 0; ni < n; ni++) {
        sendChar(n[ni]);
    }

    // Start the array
    sendChar(SCP.START_ARRAY);

    // Arrays to send:
    for (var i = 0; i < vertices.length; i++) {
        var pulseVec = normToPulses(vertices[i]);
        var timeTo = timeVector[i];
        var x = parseInt(pulseVec.x).toString();
        var y = parseInt(pulseVec.y).toString();
        var t = timeTo.toString();

        // Send x, y, and time vector, separated by ','
        for (var xi = 0; xi < x.length; xi++) {
            sendChar(x[xi]);
        }
        sendChar(SCP.ARRAY_SEPARATE);
        for (var yi = 0; yi < y.length; yi++) {
            sendChar(y[yi]);
        }
        sendChar(SCP.ARRAY_SEPARATE);
        for (var ti = 0; ti < t.length; ti++) {
            sendChar(t[ti]);
        }
        sendChar(SCP.NEXT_ENTRY);
    }
    sendChar(SCP.END_ARRAY);
}

function sendChar(c) {
    console.log(c);
    serial.write(c);
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