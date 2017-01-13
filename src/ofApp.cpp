#include "ofApp.h"

vector<ofPoint> vertices;
vector<ofColor> colors;
ofEasyCam cam;
int nTri; //The number of triangles
int nVert; //The number of the vertices equals nTri * 3
//--------------------------------------------------------------
void ofApp::setup() {
	/*ofEnableDepthTest();
	ofCamera x = ofEasyCam();
	x.begin();*/
	//x.move();
	ofBackground(255, 255, 255);

	// init random generator
	std::srand((unsigned int)std::time(0));


	grid.generateMaze();
	
	cam.enableMouseInput();
}


//--------------------------------------------------------------
void ofApp::update() {

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
	ofEnableDepthTest(); //Enable z-buffering
	//ofSetRectMode(OF_RECTMODE_CORNER);
	//ofBackgroundGradient(ofColor(255), ofColor(128));

	//ofPushMatrix(); //Store the coordinate system

	ofTranslate(ofGetWidth() / 2, /*ofGetHeight() / 2*/ 0, -200);
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
	case 32:
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
	std::cout << cam.getLookAtDir();
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
	case 'r':
		grid.partialReset();
		grid.aStarSearch();
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
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	cam.getDrag();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

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
