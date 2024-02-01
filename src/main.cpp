#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	ofGLWindowSettings settings;
	#if defined(TARGET_OSX)
	settings.setGLVersion(3,2);
	#else
	settings.setGLVersion(4,1);
	#endif
	
    settings.setSize(1280, 720);
    ofCreateWindow(settings);

    ofRunApp( new ofApp());
}
