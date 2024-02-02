#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxImGui.h"
#include "scene/sceneManager.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void exit();

	SceneManager* sceneManager;
    ofxImGui::Gui gui;
    ImVec4 backgroundColor;
};

