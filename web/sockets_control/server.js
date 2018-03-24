// 'use strict';


// ====== Get IP Address =======
var os = require('os');
var ifaces = os.networkInterfaces();

Object.keys(ifaces).forEach(function (ifname) {
    var alias = 0;

    ifaces[ifname].forEach(function (iface) {
        if ('IPv4' !== iface.family || iface.internal !== false) {
            // skip over internal (i.e. 127.0.0.1) and non-ipv4 addresses
            return;
        }

        if (alias >= 1) {
            // this single interface has multiple ipv4 addresses
            console.log(ifname + ':' + alias, iface.address);
        } else {
            // this interface has only one ipv4 adress
            console.log(ifname, iface.address);
        }
        ++alias;
    });
});

// ====== Set up Express and socket to talk to phone ======
var express = require('express');
var app = express();
var server = app.listen(8000);

app.use(express.static('public'));
console.log("Hello world; the server is alive!");

// Socket
var socket = require('socket.io');
var io = socket(server);

// Current master
var controlMaster = '';

// Even handling
io.sockets.on('connection', onNewConnection);

function onNewConnection(socket) {
    console.log('new connection: ' + socket.id);

    // Bind events
    socket.on('deviceOrientationChange', function(data) {
        socket.broadcast.emit('deviceOrientationChanged', data);
        console.log('device orientation updated');
    });

    socket.on('disconnect', function() {
        console.log('disconnected: ' + socket.id);

        if (controlMaster === socket.id) {
            controlMaster = '';
            console.log('no more control masters');
        }
    });

    socket.on('requestToBeMaster', function() {
        if (controlMaster === '') {

            // Set as new master
            controlMaster = socket.id;

            // Emit the acknowledge signal back to client
            socket.emit('requestToBeMasterResponse', true);

            console.log('new master: ', socket.id);
        }

        // Otherwise don't response (deny)
    });
}

// ====== set up serial port to talk to the arduino controller ======
var serialserver = require('p5.serialserver');
serialserver.start();
console.log("p5.serialserver is running");