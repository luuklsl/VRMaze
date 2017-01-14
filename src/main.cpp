#include "ofMain.h"
#include "ofApp.h"
#include "wtypes.h"
#include "constants.h"
#include <iostream>

void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

//========================================================================
int main() {
	int horizontal = 0;
	int vertical = 0;
	GetDesktopResolution(horizontal, vertical);
	std::cout << horizontal << '\n' << vertical << '\n';
	//ofSetupOpenGL(WINDOW_WIDTH, WINDOW_HEIGHT, OF_WINDOW);
	ofSetupOpenGL((horizontal-20), (vertical-80), OF_WINDOW);
	
	ofRunApp(new ofApp());
}
