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
    sendVerticesToController(vertices, timeVector) {

        // 
    }
}