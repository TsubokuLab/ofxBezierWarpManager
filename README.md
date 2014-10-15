# ofxBezierWarpManager

This addon is manager for multiple ofxBezierWarp.

*This addon need ofxXmlSettings*

Author : Teruaki Tsubokura (<http://teruaki-tsubokura.com/>)

![ofxBezierWarpManager](https://github.com/TsubokuLab/ofxBezierWarpManager/raw/master/screenshot/ofxBezierWarpManager.png)

## Usage
1. Import to your project.
2. Add FBO for Bezier Warp.
    first_fbo.allocate(1920, 1080);
    bezManager.addFbo(&first_fbo);
3. Draw to FBO between "begin()" and "end()"
    first_fbo.begin();
    _mov.draw(0,0,1920,1080);
    first_fbo.end();
4. Draw ofxBezierWarpManager.
    bezManager.draw();
5. Add key/mouse events.
    void ofApp::keyPressed(int key){
        bezManager.keyPressed(key);
        if(key == OF_KEY_RETURN){
            bezManager.toggleGuideVisible();
        }
        if(key == 's'){
            bezManager.saveSettings();
        }
        if(key == 'l'){
            bezManager.loadSettings();
        }
    }
    void ofApp::mouseDragged(int x, int y, int button){
        bezManager.mouseDragged(x, y, button);
     }
    void ofApp::mousePressed(int x, int y, int button){
        bezManager.mousePressed(x, y, button);
    }

## Example project
* [ENTER] key : Toggle guide visible.
* [S] key : Save settings.
* [L] key : Load settings.
* Left drag the control point : Move Corners/Anchors.
* Right click the control point : Toggle Bezier/Homoglaphy mode.
* Arrow key : Move Corners/Anchors. (selected control point)