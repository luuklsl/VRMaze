#pragma once

#include "ofMain.h"
#include "ofxOculusRiftCV1.h"
//#include "ofxOculusDK2.h"
#include "Grid.hpp"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void drawScene();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	/*ofCamera x;*/
	ofxOculusRiftCV1 cv1;
	//ofxOculusDK2 oculusRift;
	ofImage wall1;
	ofImage wall2;
	ofImage floor;
	ofImage roof;
	Grid grid;
	ofCamera cam;			//initialize a cam object (ofEasycam can access _most_ ofCamera and ofNode functions from the online documentation)
	ofFpsCounter fps;		//fps counter object
							//ofTrueTypeFont	verdana14;
	int prevX;				//initialization of values used for continuous tracking of mousemovement for camera positioning
	int prevY;				//these two should be able to be deleted with Oculus Implementation
	
	bool maze;
};
