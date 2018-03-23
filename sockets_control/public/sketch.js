
// Socket client
var socket;

function setup() {
    canvas = createCanvas(windowWidth, windowHeight);
    canvas.position(0, 0);

    socket = io.connect('http://192.168.0.101:8000');

    // Socket incoming message handling
    socket.on('mouseDraggedEvent', onMouseDraggedEvent);

    // graphics setup
    background(0);
    noStroke();
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

function draw() {
    fill(0, 50);
    rect(0, 0, width, height);
}

function onMouseDraggedEvent(data) {
    fill(255, 50, 50);
    ellipse(data.x, data.y, 20, 20);
    fill(255);
    ellipse(data.x, data.y, 10, 10);
}