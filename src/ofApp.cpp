#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// initialize the device

	bool bOK = cv1.init();

	if (!bOK) 
	{
		ofLogNotice() << "OculusRiftCV1 failed to initialize";
	}
	else 
	{
		ofLogNotice() << "Initialized OculusRiftCV1";

		ofRectangle bounds = cv1.getHMDSize();
		ofSetWindowShape(bounds.width, bounds.height);
	}
	wall1.loadImage("wall.bmp");
	//wall1.getTextureReference().bind();


	std::srand((unsigned int)std::time(0));
	ofSetVerticalSync(false);
	ofBackground(255, 255, 255);
	ofEnableDepthTest(); //Enable z-buffering
	grid.generateMaze();
}

//--------------------------------------------------------------
void ofApp::update(){
	std::stringstream strm; // every update we ''stream'' framerate
	strm << "fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());

	cv1.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofEnableDepthTest();

	// draw left eye first
	cv1.begin(ovrEye_Left);
	ofClear(0, 255, 255);
	drawScene();
	cv1.end(ovrEye_Left);

	// then right eye
	// fyi--the order is critical!
	cv1.begin(ovrEye_Right);
	ofClear(0, 255, 255);
	drawScene();
	cv1.end(ovrEye_Right);

	// display the stereo view in the OF window (optional)
	cv1.draw(0, 0);
}

//----------------------------------------------------------
void ofApp::drawScene() {

	/*ofSeedRandom(666);

	for (int i = 0; i<100; i++) {

		float theta = ofRandom(TWO_PI);
		float phi = ofRandom(PI);
		float dist = ofRandom(0.5, 5.0);
		float brightness = ofRandom(255);

		ofVec3f pos;
		pos.x = cos(theta) * sin(phi) * dist;
		pos.y = sin(theta) * sin(phi) * dist;
		pos.z = cos(phi) * dist;

		ofSetColor(brightness);

		ofPushMatrix();
		ofTranslate(pos);
		ofDrawBox(0.5);
		ofPopMatrix();
	}*/
	//cam.begin(); //<<--look into exact use of this 
	grid.draw();

	ofDrawAxis(5000);
	//cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 32: //space key
		cam.boom(10);
		break;
	case 'z':
		cam.boom(-10);
		break;
	case 'w':
		cam.dolly(-10);
		break;
	case 's':
		cam.dolly(10);
		break;
	case 'a':
		//cam.pan(-10);
		cam.truck(-10);
		break;
	case 'd':
		//cam.pan(+10);
		cam.truck(10);
		break;
	case 'q':
		cam.roll(2);
		break;
	case 'e':
		cam.roll(-2);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key) {
	case 'm':
		grid.reset();
		grid.generateMaze();
		break;
		/*case 'r':
		grid.reset();
		grid.generateRooms();
		break;
		case 'o':
		grid.reset();
		grid.generateObstacles();
		break;
		case 'j':
		grid.reset();
		grid.generateJail();
		break;`*/
	case 'f':
		grid.partialReset();
		grid.depthFirstSearch();
		break;
	case 'b':
		grid.partialReset();
		grid.breadthFirstSearch();
		break;
	case 'g':
		grid.partialReset();
		grid.greedySearch();
		break;
	case 't': //get better key assigned <<
		grid.partialReset();
		grid.aStarSearch();
		break;
	case 'r':
		grid.partialReset();
		break;
		/*case 't':
		system("cls");
		std::cout << "Search	|	Visited	|  Path length	|	PL/V"<<std::endl;
		grid.partialReset();
		grid.aStarSearch();
		grid.partialReset();
		grid.greedySearch();
		grid.partialReset();
		grid.breadthFirstSearch();
		grid.partialReset();
		grid.depthFirstSearch();
		break;*/
	case 'y':
		ofExit();
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (button == 0)
	{
		cam.pan((x - prevX) / 3.6);
		cam.tilt((y - prevY) / 3.6);
		prevX = x;
		prevY = y;
		std::cout << cam.getRoll() << std::endl;
		cam.roll(0);
	}
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (button == 0)
	{
		prevX = x;
		prevY = y;
		std::cout << x << " " << y << std::endl;
	}

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
