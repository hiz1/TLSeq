#include "ofApp.h"

ofVec2f tilePos(int xi, int yi) {
    int baseX = - (TILECOL * (TILESIZE + MARGIN) - MARGIN) / 2;
    int baseY = - (TILEROW * (TILESIZE + MARGIN) - MARGIN) / 2;
    return ofVec2f(baseX + xi * (TILESIZE + MARGIN) + TILESIZE/2, baseY + yi * (TILESIZE + MARGIN) + TILESIZE/2);
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    camera.setPosition(0, 0, 700);
    pos = ofVec2f(int(TILEROW/2), 3);
    
    phase = new TimerPhase(ofVec2f(10, 10), 400, 120);
}

//--------------------------------------------------------------
void ofApp::update(){
    camera.lookAt(ofVec3f::zero());
    
    if(phase != NULL) {
        if(phase->update()) phase = NULL;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    camera.begin();
    
    ofPushMatrix();
    ofRotate(-20, 1, 0, 0);
    int baseX = - (TILECOL * (TILESIZE + MARGIN) - MARGIN) / 2;
    int baseY = - (TILEROW * (TILESIZE + MARGIN) - MARGIN) / 2;
    for(int xi=0;xi<TILECOL;xi++) {
        for(int yi=0;yi<TILEROW;yi++) {
            int x = xi * (TILESIZE + MARGIN);
            int y = yi * (TILESIZE + MARGIN);
            ofSetColor(122 + (yi % 2) * 10);
            ofFill();
            ofVec2f pos = tilePos(xi, yi);
            ofRect(pos.x - TILESIZE/2, pos.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
        }
    }
    
    ofSetColor(255);
    ofNoFill();
    ofVec2f p = tilePos(pos.x, pos.y);
    ofDrawSphere(p.x, p.y, 20, 40);
    
    ofPopMatrix();
    camera.end();
    
    if(phase != NULL) {
        phase->draw();
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_UP   )pos.y ++;
    if(key == OF_KEY_DOWN )pos.y --;
    if(key == OF_KEY_LEFT )pos.x --;
    if(key == OF_KEY_RIGHT)pos.x ++;
    
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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