var serial;

function setup() {
    serial = new p5.SerialPort();

    serial.on('connected', onServerConnected);
    serial.on('list', onListUpdate);
    serial.on('error', onError);
    serial.on('data', SerialEvent)
}

function onServerConnected() {
    console.log('Server connected');
}

function onListUpdate(list) {
    html = '';

    for (var i = 0; i < list.length; i++) {
        console.log(i + " " + list[i]);
        html += '<button class="port-btn" id="' + list[i] + '">' + list[i] + '</button>';
    }

    if (rebindListButtons !== undefined) rebindListButtons();
}

function onPortSelect(port) {
    serial.open(port, { baudRate: 115200 }, onOpen);

    // close ui
    if (startedSerial !== undefined) startedSerial();
}

function onSerialStop() {
    // Close serial
    serial.close();
    console.log('Serial port closed');
    if (endedSerial !== undefined) endedSerial();
}

function SerialEvent() {
    if (serial.available()) {
        var c = serial.readChar();

        if (c === '$') {
            return;
        } else {
            displayData(c);
        }
    }
    serial.clear();
}

function onError(err) {
    console.log(err);
}

function onOpen() {
    console.log('Serial port opened');
}
