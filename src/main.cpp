#include "ofMain.h"
#include "ofApp.h"

#include "constants.h"
#include <iostream>


//========================================================================
int main() {    
	ofSetupOpenGL(WINDOW_WIDTH, WINDOW_HEIGHT, OF_WINDOW);
	ofRunApp(new ofApp());
}
