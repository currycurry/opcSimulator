#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    effect = 0;
    hide = false;
    pressed = false;
    scalar = 0;
    fullscreen = false;
    
    // Connect to the fcserver
    opcClient.setup("127.0.0.1", 7890);
    
    // You define the stage size and draw into the stage
    opcClient.setupStage(700, 700);
    
    effects = false;
    
    defaultEffects.setup(opcClient.getStageCenterX(), opcClient.getStageCenterY(), opcClient.getStageWidth(), opcClient.getStageHeight());
    

    ////criss cross triangle
    for (int x = 0; x < 10; x++) {
        strips.push_back( ofxNeoPixelStrip( 60 * x, 600, floor( 10.4 + 10.4 * ( 10 - x )), 5, 2 * PI / 3
                                           ));
    }
    for (int x = 0; x < 11; x++) {
        strips.push_back( ofxNeoPixelStrip( 60 * x + 60, 600, floor( 6 + 6 * x ), 5, 7 * PI / 6
                                           ));
    }
    
    ////converging triangle
    for ( int x = 0; x < 10; x ++ ) {
        strips.push_back( ofxNeoPixelStrip( 60 * x, 600, floor( 10.4 + 10.4 * ( 10 - x )), 5, 2 * PI / 3
                                           ));
    }
        
    
    ofRectangle current_building;
    current_building.set( 10, 10, 100, 100 );
    
    current_color.setup();
    build_color = current_color.getCurrentColor();



}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetFullscreen( fullscreen );
    
    ofSetWindowTitle("opcSimulator");
    
    opcClient.update();
    current_color.update();
    
    // Now Draw the effects to the stage
    opcClient.beginStage();
    
    // Draw what you want rendered here
    // For now here are some default effects
    if ( effects ) { //switch through different effects with right and left arrows
        defaultEffects.draw(effect);
    }
    
    else { //toggle to show the colorful growing rectangle by pressing e
        ofSetColor( build_color );
        ofRectangle current_building;
        current_building.set( mouseX - scalar / 4, mouseY - scalar, scalar / 3 , scalar  );
        ofDrawRectangle( current_building );
    }
    
    
    opcClient.endStage();
    
    // New Get Method
    for (int i = 0; i < strips.size(); i++) {
        opcClient.getStagePixels(strips[i].getPixelCoordinates(), strips[i].colors);
    }
    
    // If the client is not connected do not try and send information
    if (!opcClient.isConnected()) {
        // Will continue to try and reconnect to the Pixel Server
        opcClient.tryConnecting();
    }
    else {
        // Write out the data
        for (int i = 0; i < strips.size(); i++) {
            opcClient.writeChannel(i, strips[i].colorData());
        }
    }
    
    if ( pressed ) {
        scalar ++;
        cout << "scalar: " << scalar << endl;
    }


}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    opcClient.drawStage(hide);
    
    // Show the grabber area and Draw the output
    for (int i = 0; i < strips.size(); i++) {
        strips[i].drawGrabRegion(hide);
        strips[i].draw((opcClient.getStageWidth() + 25)+( i * 25 ), 10);
    }
    
    // Report Messages
    /*stringstream ss;
    ss << "Press Left and Right to Change Effect Mode" << endl;
    ss << "FPS: " << ofToString((int)(ofGetFrameRate())) << endl;
    ofDrawBitmapStringHighlight(ss.str(), 5,ofGetHeight()-30);*/


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if ( key == 'e' ) {
        effects = !effects;
    }
    
    if (key == OF_KEY_LEFT) {
        effect--;
    }
    if (key == OF_KEY_RIGHT) {
        effect++;
    }
    if (key == ' ') {
        hide = !hide;
    }
    
    if ( key == 'f') {
        fullscreen = !fullscreen;
    }
    
   
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    scalar = 0;
    pressed = true;
    build_color = current_color.getCurrentColor();

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    //ofRectangle current_building( mouseX - scalar / 4, mouseY - scalar, scalar / 2 , scalar );
    //buildings.push_back( current_building );
    pressed = false;
    //scalar = 0;
    cout << "scalar: " << scalar << endl;

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
//--------------------------------------------------------------
void ofApp::exit()
{
    // Close Connection
    opcClient.close();
    
}
