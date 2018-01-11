#include "ofxBezierWarpManager.h"

//--------------------------------------------------------------
ofxBezierWarpManager::ofxBezierWarpManager(){
    bBezierGuide = true;
}

//--------------------------------------------------------------
void ofxBezierWarpManager::setup(int _resolution){
    warpResolution = _resolution;
}

//--------------------------------------------------------------
void ofxBezierWarpManager::setWarpResolution(int _resolution){
    warpResolution = _resolution;
}

//--------------------------------------------------------------
void ofxBezierWarpManager::update() {
	// update bezier
	for (int i = 0; i < bezierList.size(); i++) {
		bezierList[i].update();
	}
}

//--------------------------------------------------------------
void ofxBezierWarpManager::draw(){
    // draw bezier
    for (int i = 0; i < bezierList.size(); i++) {
        bezierList[i].draw();
    }
}

void ofxBezierWarpManager::nextHandle(){
    // draw bezier
    for (int i = 0; i < bezierList.size(); i++) {
        bezierList[i].nextHandle();
    }
}

//--------------------------------------------------------------
void ofxBezierWarpManager::keyPressed(int key){
    for( int i = 0; i < bezierList.size(); i++){
        bezierList[i].keyPressed(key);
    }
}

//--------------------------------------------------------------
void ofxBezierWarpManager::keyReleased(int key){

}


//--------------------------------------------------------------
void ofxBezierWarpManager::mouseDragged(int x, int y, int button){
    for( int i = 0; i < bezierList.size(); i++){
        bezierList[i].mouseDragged(x, y, button);
    }
}

//--------------------------------------------------------------
void ofxBezierWarpManager::mousePressed(int x, int y, int button){
    for( int i = 0; i < bezierList.size(); i++){
        bezierList[i].mousePressed(x, y, button);
    }
}

//--------------------------------------------------------------
void ofxBezierWarpManager::addFbo(ofFbo* _fbo){
    cout << "[ofxBezierWarpManager] addFbo(ofFbo* _fbo)" << endl;
    ofxBezierWarp _bezier;
    _bezier.setup(_fbo);
    _bezier.setWarpResolution(warpResolution);
    bezierList.push_back(_bezier);
}

//--------------------------------------------------------------
void ofxBezierWarpManager::removeFbo(){
    bezierList.pop_back();
}

//--------------------------------------------------------------
void ofxBezierWarpManager::clear(){
    bezierList.clear();
    maskList.clear();
}

//--------------------------------------------------------------
void ofxBezierWarpManager::saveSettings(){
    //screen settings
    ofxXmlSettings _xml = ofxXmlSettings();
	int lastTagNumber;
    // screen
    for (int m = 0; m < bezierList.size(); m++) {
        lastTagNumber = _xml.addTag("SCREEN");
        _xml.setValue("SCREEN:IS_BEZIER", (int)bezierList[m].anchorControl, lastTagNumber);
        _xml.setValue("SCREEN:RESOLUTION", (int)bezierList[m].prev_gridRes, lastTagNumber);
        if( _xml.pushTag("SCREEN", lastTagNumber) ){
            for (int c = 0; c < 4; c++) {
                int tagNum = _xml.addTag("CORNER");
                _xml.setValue("CORNER:X", (int)bezierList[m].corners[c].x, tagNum);
                _xml.setValue("CORNER:Y", (int)bezierList[m].corners[c].y, tagNum);
            }
            for (int a = 0; a < 8; a++) {
                int tagNum = _xml.addTag("ANCHOR");
                _xml.setValue("ANCHOR:X", (int)bezierList[m].anchors[a].x, tagNum);
                _xml.setValue("ANCHOR:Y", (int)bezierList[m].anchors[a].y, tagNum);
            }
            _xml.popTag();
        }
    }
	
	_xml.saveFile("BezierWarpManager_settings.xml");
}

//--------------------------------------------------------------
void ofxBezierWarpManager::loadSettings(){
    ofxXmlSettings _xml;
    
	if( _xml.loadFile("BezierWarpManager_settings.xml") ){
		cout << "[BezierWarpManager_settings.xml] loaded!" << endl;
	}else{
		cout << "unable to load [BezierWarpManager_settings.xml] check data/ folder" << endl;
        return;
	}
    
	int numMovieTags = _xml.getNumTags("SCREEN");
    
    // screen
	for(int n = bezierList.size(); n < numMovieTags; n++){
        // add bezier
        ofxBezierWarp _bezier;
        bezierList.push_back(_bezier);
    }
    for(int m = 0; m < numMovieTags; m++){
		_xml.pushTag("SCREEN", m);
        ofLog(OF_LOG_NOTICE," SCREEN:" + ofToString(m));
        
        bezierList[m].anchorControl = _xml.getValue("IS_BEZIER", 0);
        bezierList[m].gridRes = _xml.getValue("RESOLUTION", 10);
        bezierList[m].prev_gridRes = bezierList[m].gridRes;
        ofLog(OF_LOG_NOTICE," IS_BEZIER:" + ofToString(bezierList[m].anchorControl));
        ofLog(OF_LOG_NOTICE," RESOLUTION:" + ofToString(bezierList[m].prev_gridRes));
		int numCornerTags = _xml.getNumTags("CORNER");
		for(int i = 0; i < numCornerTags; i++){
			int x = _xml.getValue("CORNER:X", 0, i);
			int y = _xml.getValue("CORNER:Y", 0, i);
			bezierList[m].corners[i].x = x;
            bezierList[m].corners[i].y = y;
			ofLog(OF_LOG_NOTICE," CORNER:" + ofToString(i) + " x:"+ ofToString(x) + " y:" + ofToString(y));
		}
		int numAnchorTags = _xml.getNumTags("ANCHOR");
		for(int i = 0; i < numAnchorTags; i++){
			int x = _xml.getValue("ANCHOR:X", 0, i);
			int y = _xml.getValue("ANCHOR:Y", 0, i);
			bezierList[m].anchors[i].x = x;
            bezierList[m].anchors[i].y = y;
			ofLog(OF_LOG_NOTICE," ANCHOR:" + ofToString(i) + " x:"+ ofToString(x) + " y:" + ofToString(y));
		}
		_xml.popTag();
	}
}

//--------------------------------------------------------------
void ofxBezierWarpManager::setGuideVisible(bool _visible, int _bezierNum){
    if(_bezierNum <= -1){
        bBezierGuide = _visible;
        for( int i = 0; i < bezierList.size(); i++){
            bezierList[i].setGridVisible(bBezierGuide);
        }
    }else{
        for( int i = 0; i < bezierList.size(); i++){
            if(i == _bezierNum) bezierList[i].setGridVisible(_visible);
        }
    }
}

//--------------------------------------------------------------
void ofxBezierWarpManager::toggleGuideVisible(int _bezierNum){

	if (_bezierNum <= -1) {
		bBezierGuide = !bBezierGuide;
		for (int i = 0; i < bezierList.size(); i++) {
			bezierList[i].setGridVisible(bBezierGuide);
		}
	}
	else {
		for (int i = 0; i < bezierList.size(); i++) {
			if (i == _bezierNum) bezierList[i].setGridVisible(!bezierList[i].showGrid);
		}
	}
}
