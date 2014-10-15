#pragma once

#include "ofMain.h"
#include "ofxBezierWarpManager.h"

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
    
    ofxBezierWarpManager bezManager;
    
    // 描画したいFBO
    ofFbo first_fbo;
    ofFbo second_fbo;
    ofFbo third_fbo;
    ofFbo fourth_fbo;
    
    bool showGuide;
    
    // 描画する映像の代わり
    ofVideoGrabber _mov;
};
