var socket

var x, y;
var xR, yR;

var isConnected;

function setup() {
    createCanvas(500, 500);
    setupOsc(12000, 8000); //3334);
    isConnected = false;
}

function draw() {
    background(0, 0, 255);
    fill(0, 255, 0);
    ellipse(x, y, 100, 100);
    fill(0);
    text("I'm p5.js", x-25, y);

    xR = mouseX-50;
    yR = mouseY-50;
    fill(0, 255, 255);
    rect(xR, yR, 100, 100);
    fill(0);
    text("I'm p5.js", mouseX-25, mouseY);


    // send these over OSC to AbletonOSC after you've selected 8 parameters to modify
    if (isConnected) {
        socket.emit('message',  '/pos', [xR,yR]);
    }
}

function receiveOsc(address, value) {
    console.log("received OSC: " + address + ", " + value);

    if (address == '/test') {
        x = value[0];
        y = value[1];
    }
}


function setupOsc(oscPortIn, oscPortOut) {
    socket = io.connect('http://127.0.0.1:8081', { port: 8081, rememberTransport: false });
    socket.on('connect', function() {
        socket.emit('config', {	
            server: { port: oscPortIn,  host: '127.0.0.1'},
            client: { port: oscPortOut, host: '127.0.0.1'}
        });
    });
    socket.on('connect', function() {
        isConnected = true;
    });

    socket.on('message', function(msg) {
        if (msg[0] == '#bundle') {
            for (var i=2; i<msg.length; i++) {
                receiveOsc(msg[i][0], msg[i].splice(1));
            }
        } else {
            receiveOsc(msg[0], msg.splice(1));
        }
    });
}
