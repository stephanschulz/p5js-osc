#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("oscReceiveExample");
    ofSetFrameRate(60); // run at 60 fps
    ofSetVerticalSync(true);
    
    // open an outgoing connection to HOST:PORT
    sender.setup(HOST, PORT);
    
    // listen on the given port
    ofLog() << "listening for osc messages on port " << LISTEN_PORT;
    receiver.setup(LISTEN_PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(old_x != ofGetMouseX() || old_y != ofGetMouseY()){
        old_x = ofGetMouseX();
        old_y = ofGetMouseY();
        ofxOscMessage m;
        m.setAddress("/test");
        m.addIntArg(ofGetMouseX());
        m.addIntArg(ofGetMouseY());
        sender.sendMessage(m, false);
    }
    
    // hide old messages
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        if(timers[i] < ofGetElapsedTimef()){
            msgStrings[i] = "";
        }
    }
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if(m.getAddress() == "/pos"){
            
            // first argument is int32, second is a string
            xR = m.getArgAsInt32(0);
            yR = m.getArgAsInt32(1);
        }
        else{
            
            // unrecognized message: display on the bottom of the screen
            string msgString;
            msgString = m.getAddress();
            msgString += ":";
            for(size_t i = 0; i < m.getNumArgs(); i++){
                
                // get the argument type
                msgString += " ";
                msgString += m.getArgTypeName(i);
                msgString += ":";
                
                // display the argument - make sure we get the right type
                if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                    msgString += ofToString(m.getArgAsInt32(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                    msgString += ofToString(m.getArgAsFloat(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                    msgString += m.getArgAsString(i);
                }
                else{
                    msgString += "unhandled argument type " + m.getArgTypeName(i);
                }
            }
            
            // add to the list of strings to display
            msgStrings[currentMsgString] = msgString;
            timers[currentMsgString] = ofGetElapsedTimef() + 5.0f;
            currentMsgString = (currentMsgString + 1) % NUM_MSG_STRINGS;
            
            // clear the next line
            msgStrings[currentMsgString] = "";
        }
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(100, 0);
    
    ofSetColor(0, 255, 0);
    ofFill();
    ofDrawCircle(mouseX, mouseY, 50);
    ofSetColor(0);
    ofDrawBitmapString("I'm OF", mouseX-20, mouseY);
    
    ofSetColor(0, 255, 255);
    ofFill();
    ofDrawRectangle(xR, yR, 100, 100);
    ofSetColor(0);
    ofDrawBitmapString("I'm OF", xR+20, yR+50);
    
    // draw recent unrecognized messages
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        ofDrawBitmapStringHighlight(msgStrings[i], 10, 40 + 15 * i);
    }
    
    string buf = "listening for osc messages on port " + ofToString(PORT);
    ofDrawBitmapStringHighlight(buf, 10, 20);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
