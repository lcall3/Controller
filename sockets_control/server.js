
// Express
var express = require('express');
var app = express();
var server = app.listen(8000);

app.use(express.static('public'));
console.log("Hello world; the server is alive!");

// Socket
var socket = require('socket.io');
var io = socket(server);

// Even handling
io.sockets.on('connection', onNewConnection);


function onNewConnection(socket) {
    console.log('new connection: ' + socket.id);

    // Bind rest of the events
    socket.on('mouseDragged', onMouseDragged);
    socket.on('deviceOrientationChange', onDeviceOrientationChange);

    function onMouseDragged(data) {

        // Broadcast the data back to all clients
        socket.broadcast.emit('mouseDraggedEvent', data);
    }

    function onDeviceOrientationChange(data) {
        socket.broadcast.emit('rotateEvent', data);
        console.log(data);
    }
}