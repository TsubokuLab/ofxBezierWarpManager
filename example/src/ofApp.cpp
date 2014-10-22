#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // 描画する映像の代わり
    _mov.initGrabber(640, 360);
    
    first_fbo.allocate(1920, 1080);
    second_fbo.allocate(1920, 1080);
    third_fbo.allocate(1920, 1080);
    fourth_fbo.allocate(1920, 1080);
    
    bezManager.setup(10); //WarpResolution
    bezManager.addFbo(&first_fbo);
    bezManager.addFbo(&second_fbo);
    bezManager.addFbo(&third_fbo);
    bezManager.addFbo(&fourth_fbo);
    
    bezManager.loadSettings();
}

//--------------------------------------------------------------
void ofApp::update(){
    // 映像更新
    _mov.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0);
    
    // Fboの中を更新 //////////////////////
    first_fbo.begin();
    _mov.draw(0,0,1920,1080);
    first_fbo.end();
    
    second_fbo.begin();
    _mov.draw(0,0,1920,1080);
    second_fbo.end();
    
    third_fbo.begin();
    _mov.draw(0,0,1920,1080);
    third_fbo.end();
    
    fourth_fbo.begin();
    _mov.draw(0,0,1920,1080);
    fourth_fbo.end();
    /////////////////////////////////////
    
    // ベジエワープ描画
    bezManager.draw();
    
    string _help = "[ENTER] key : Toggle guide visible.\n";
    _help += "[S] key : Save settings.\n";
    _help += "[L] key : Load settings.\n";
    _help += "Left drag the control point : Move Corners/Anchors.\n";
    _help += "Right click the control point : Toggle bezier/homoglaphy mode.\n";
    _help += "Arrow key : Move Corners/Anchors. (selected control point)\n";
    ofDrawBitmapString(_help, 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // キーイベントを転送
    bezManager.keyPressed(key);
    
    // ガイド表示/非表示
    if(key == OF_KEY_RETURN){
        bezManager.toggleGuideVisible();
    }
    // 設定保存
    if(key == 's'){
        bezManager.saveSettings();
    }
    // 設定読込
    if(key == 'l'){
        bezManager.loadSettings();
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
    // マウスドラッグイベントを転送
    bezManager.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // マウスプレスイベントを転送
    bezManager.mousePressed(x, y, button);
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
