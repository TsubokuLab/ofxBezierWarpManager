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
    
        void setup(int _resolution = 10);
        void setWarpResolution(int _resolution);
		void update(); // if you need
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
    
    void addFbo(ofFbo* _fbo);
    void removeFbo();
    void clear();
    
    void nextHandle();
    void saveSettings();
    void loadSettings();
    
    void setGuideVisible(bool _visible, int _bezierNum = -1);
    void toggleGuideVisible(int _bezierNum = -1);
    
    vector<ofxBezierWarp> bezierList;
    vector<ofxBezierWarp> maskList;
    
    int warpResolution;
    bool bBezierGuide;
    bool bGradient;
    ofImage gradientImg;
    ofFbo gradientFbo;
    ofFbo blackFbo;
};
