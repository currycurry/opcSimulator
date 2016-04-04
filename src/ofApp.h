#pragma once

#include "ofMain.h"
#include "ofxOPC.h"
#include "currentColor.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        //ofRectangle current_building;

        ofColor build_color;
        currentColor current_color;

        ofxOPC opcClient;
        bool effects;
        bool fullscreen;
    
        //vector<ofRectangle> buildings;
    
        deque <ofxNeoPixelStrip> strips;
        Effects defaultEffects;
        
        int effect;
        bool hide;
    
        int scalar;
        bool pressed;
		
};
