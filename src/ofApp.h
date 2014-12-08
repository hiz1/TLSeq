#pragma once

#include "ofMain.h"
#include "TimerTL.h"

#define TILESIZE 80
#define MARGIN   4
#define TILECOL  12
#define TILEROW  7

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
private:
    ofCamera camera;
    ofVec2f  pos;
    vector<TL *> timelines;
};
