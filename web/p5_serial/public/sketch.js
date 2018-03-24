var serial;

function setup() {
    serial = new p5.SerialPort();

    serial.on('connected', onServerConnected);
    serial.on('list', onListUpdate);
    serial.on('data', onData);
    serial.on('error', onError);
    serial.on('open', onOpen);
}

function onServerConnected() {
    console.log('Server connected');
}

function onListUpdate(list) {
    html = '';

    for (var i = 0; i < list.length; i++) {
        console.log(i + " " + list[i]);
        html += '<button id="' + list[i] + '">' + list[i] + '</button>';
    }

    $('#port-select').html(html);
}

function onData() {
    while (serial.available()) {
        console.log(serial.readStringUntil('\n'));
    }
}

function onError(err) {
    console.log(err);
}

function onOpen() {
    console.log('Serial port opened');
}
