#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    
    
    
    timelines.push_back(new TimerTL(ofVec2f(10, 10), 400, 120));
    timelines.push_back(new TimerTL(ofVec2f(500, 10), 200, 60));
    timelines.push_back(new GameTL());
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    for(ofxTL *tl : timelines) {
        if(tl != NULL) {
            if(tl->update()) tl = NULL;
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    for(ofxTL *tl : timelines) {
        if(tl != NULL) {
            tl->draw();
        }
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    for(ofxTL *tl : timelines) {
        if(tl != NULL) {
            tl->keyPressed(key);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    for(ofxTL *tl : timelines) {
        if(tl != NULL) {
            tl->keyReleased(key);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    for(ofxTL *tl : timelines) {
        if(tl != NULL) {
            tl->mouseMoved(x, y);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    for(ofxTL *tl : timelines) {
        if(tl != NULL) {
            tl->mouseDragged(x, y, button);
        }
    }

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    for(ofxTL *tl : timelines) {
        if(tl != NULL) {
            tl->mousePressed(x, y, button);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    for(ofxTL *tl : timelines) {
        if(tl != NULL) {
            tl->mouseReleased(x, y, button);
        }
    }
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
