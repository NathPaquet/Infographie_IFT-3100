#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxImGui.h"
#include "Cursor.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void exit();

    ofxImGui::Gui gui;
	ofEasyCam camera;
	Cursor cursor = Cursor(CursorType::DRAWING);
    ImVec4 backgroundColor;
};

