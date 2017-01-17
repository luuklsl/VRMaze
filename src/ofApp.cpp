#include "ofApp.h"

vector<ofPoint> vertices;
vector<ofColor> colors;
ofEasyCam cam;
ofFpsCounter fps;
bool mousePressed;
int prevX;
int prevY;
int nTri; //The number of triangles
int nVert; //The number of the vertices equals nTri * 3
//--------------------------------------------------------------
void ofApp::setup() {

	ofBackground(255, 255, 255);
	cam.setAutoDistance(false);
	
	// init random generator
	std::srand((unsigned int)std::time(0));


	grid.generateMaze();
	ofEnableDepthTest(); //Enable z-buffering

	cam.disableMouseInput();
	cam.setGlobalPosition((0.5 * GRID_ELEMENT_HEIGHT), (0.5 * GRID_ELEMENT_HEIGHT), (0.5 * GRID_ELEMENT_HEIGHT));
}


//--------------------------------------------------------------
void ofApp::update() {
	std::stringstream strm;
	strm << "fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());
	//std::cout<<cam.getPosition()<<std::endl;

}

//--------------------------------------------------------------
void ofApp::draw() {

	cam.begin();

	//Negative Zpoint --> Away from player

	//grid.draw();
	/*ofSetColor(200, 200, 200, 100);
	ofRect(0, 0, 0, 200, 500);
	ofSetColor(0);
	ofLine(0, 0, 0, 200, 150, -300);*/
	//ofSetRectMode(OF_RECTMODE_CORNER);
	//ofBackgroundGradient(ofColor(255), ofColor(128));

	//ofPushMatrix(); //Store the coordinate system

	//ofTranslate(ofGetWidth() / 2, /*ofGetHeight() / 2*/ 0, -200);
	//float time = ofGetElapsedTimef(); //Get time in seconds
	//float angle = time * 10; //Compute angle. We rotate at speed 10 degrees per second
	//ofRotate(angle, 0, 1, 0); //Rotate the coordinate system along y axis
	//ofSphere(0,0,0,GRID_ELEMENT_HEIGHT/2);

	grid.draw();

	ofDrawAxis(5000);
	//for (int i = 0; i < nTri; i++) {
	//	ofSetColor(colors[i]);
	//	ofTriangle(vertices[i * 3],
	//		vertices[i * 3 + 1],
	//		vertices[i * 3 + 2]); //Draw triangle
	//}
	//ofPopMatrix(); //Restore the coordinate system
	cam.end();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
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
	}
	//std::cout << cam.getLookAtDir();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
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
	case 'e':
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
	case 'q':
		ofExit();
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (button == 0)
	{
		prevX = x;
		prevY = y;
		std::cout << x<<" "<< y << std::endl;
	}
	
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	//std::cout<<x<<" , " <<y<<std::endl;
	if (button == 0)
	{
		cam.pan((x - prevX)/3.6);
		cam.tilt((y - prevY)/3.6);
		prevX = x;
		prevY = y;
		std::cout << cam.getRoll() << std::endl;
		cam.roll(0);
	}
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
