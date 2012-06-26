#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
    ofAppGlutWindow window;
		//	ofSetupOpenGL(&window, 700,411, OF_FULLSCREEN);	
	ofSetupOpenGL(&window, 500,500, OF_WINDOW);	
	ofRunApp( new testApp());
}
