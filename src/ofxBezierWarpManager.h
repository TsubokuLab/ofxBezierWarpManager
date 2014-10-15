/*
 *  ofxBezierWarpManager.h
 *
 *  Created by Teruaki Tsubokura on 14-10-15.
 *	Manager of multiple Bezier Warp.
 *
 */

#include "ofMain.h"
#include "ofxBezierWarp.h"
#include "ofxXmlSettings.h"

class ofxBezierWarpManager{

	public:
        ofxBezierWarpManager();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
    
    void addFbo(ofFbo* _fbo);
    void removeFbo();
    void clear();
    
    void saveSettings();
    void loadSettings();
    
    void setGuideVisible(bool _visible);
    void toggleGuideVisible();

    
    vector<ofxBezierWarp> bezierList;
    
    
    bool bGuide;
};
