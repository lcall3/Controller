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

// This wraps the functionalities that's responsible for communicating to the
// controller via serial


const SCP = {
    PARSE_ARRAY: '#',
    START_ARRAY: '@',
    ARRAY_SEPARATE: ',',
    NEXT_ENTRY: '&',
    END_ARRAY: '!'
};

class Cereal {
    constructor() {
        // Serial port object
        this.serial = new p5.SerialPort();

        this.serial.on('connected', this.connectHandler);
        this.serial.on('list', this.listHandler);
        this.serial.on('error', this.errorHandler);
        this.serial.on('data', this.dataHandler);

        // Default connected serial port is undefined
        this.connectedPort = undefined;
    }

    // Select serial port function
    commence(port, baudrate) {

        // Connect to the selected serial port
        serial.open(port, {baudRate: baudrate}, function() {
            console.log('Serial port opened at ' + port);
        });

        // Call the document object to close the port selector
        if (hideSerialPorts !== undefined) {
            hideSerialPorts();
        } else {
            console.error('Cereal commence function cannot find hideSerialPorts function');
        }

        // Set currently connected port to the opened port
        this.connectedPort = port;
    }

    // Disconnect
    disconnect() {
        this.serial.close();
        console.log('Serial port closed');
        this.connectedPort = undefined;
    }

    // Handler functions
    connectHandler() {
        console.log('Serial server active; awaiting devices');
    }

    listHandler(list) {
        if (list.length !== 0) {
            console.log('Serial port available; serial port list updated');
            if (listSerialPorts !== undefined) {
                listSerialPorts(list);
            } else {
                console.error('Cereal list handler cannot find listSerialPorts function');
            }
        }
    }

    errorHandler(err) {
        console.error(err);
    }

    dataHandler(data) {
        if (this.serial.available()) {
            var inChar = this.serial.readChar();
            console.log(this.connectedPort + ': ' + inChar);
        }
    }

    // Send a single character
    sendChar(c) {
        console.log(c);
        this.serial.write(c);
    }

    // Sends serialized data to controller
    sendVerticesToController(vertices, timeVector, space) {

        // Check that serial device is connected
        if (this.connectedPort === undefined) {
            alert('Need to connect to a serial device first!');
            return;
        }

        // Check that the input is correct
        if (vertices.length != timeVector.length) {
            console.error('Ill-formed vertex/time vector');
            return;
        }

        // Send character to commence the array sequence
        this.sendChar(SCP.PARSE_ARRAY);

        // Send the length of the array
        var n = vertices.length;
        var ns = parseInt(n).toString();
        for (var i = 0; i < ns.length; i++) {
            this.sendChar(ns[i]);
        }

        // Send character to start the entries in the array
        this.sendChar(SCP.START_ARRAY);

        // Send array elements
        for (var j = 0; j < n; j++) {

            // Get string form
            var pulseVec = space.normToLaser(vertices[i]);
            var timeTo = timeVector[i];
            var x = parseInt(pulseVec.x).toString();
            var y = parseInt(pulseVec.y).toString();
            var t = timeTo.toString();

            // Send x, y, and time separated by separator
            for (var xi = 0; xi < x.length; xi++) {
                this.sendChar(x[xi]);
            }
            this.sendChar(SCP.ARRAY_SEPARATE);
            for (var yi = 0; yi < y.length; yi++) {
                this.sendChar(y[yi]);
            }
            this.sendChar(SCP.ARRAY_SEPARATE);
            for (var ti = 0; ti < t.length; ti++) {
                this.sendChar(t[ti]);
            }
            this.sendChar(SCP.NEXT_ENTRY);
        }

        // End array character
        this.sendChar(SCP.END_ARRAY);

        // Alert user
        alert(vertices.length + ' vertices sent to the controller');
    }
}