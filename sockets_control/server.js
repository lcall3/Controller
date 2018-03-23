// 'use strict';

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
io.sockets.on('disconnection', onDisconnection);


function onNewConnection(socket) {
    console.log('new connection: ' + socket.id);

    // Bind events
    socket.on('deviceOrientationChange', onDeviceOrientationChange);

    function onDeviceOrientationChange(data) {
        socket.broadcast.emit('rotateEvent', data);
        console.log(data);
    }
}

function onDisconnection(socket) {
    console.log('disconnected: ' + socket.id);
}