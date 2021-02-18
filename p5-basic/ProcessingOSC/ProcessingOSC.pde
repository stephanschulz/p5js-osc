/**
 this Processing sketch will send its mouse
 position over OSC to the p5.js sketch in the folder "p5-basic".
 you need the library OscP5 to run it.
 */

import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation;

int xR, yR;

void setup() {
  size(500, 500);
  oscP5 = new OscP5(this, 8000);
  myRemoteLocation = new NetAddress("127.0.0.1", 12000);
}


void draw() {
  background(0);
  fill(0,255,0);
  ellipse(mouseX, mouseY, 100, 100);
  fill(0);
  text("I'm Processing", mouseX-40, mouseY);


  fill(0,255,255);
  rect(xR, yR, 100, 100);
  fill(0);
  text("I'm Processing", xR+5, yR+50);
  
  // send mouse position over OSC
  OscMessage myMessage = new OscMessage("/test");
  myMessage.add(mouseX);
  myMessage.add(mouseY);
  oscP5.send(myMessage, myRemoteLocation);
}

/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  println("### received an osc message.");

  if (theOscMessage.checkAddrPattern("/pos")==true) {
      xR= theOscMessage.get(0).intValue();
      yR = theOscMessage.get(1).intValue();
      println("x,y "+xR + "," + yR);

  } 

  print(" addrpattern: "+theOscMessage.addrPattern());
  println(" typetag: "+theOscMessage.typetag());
}
