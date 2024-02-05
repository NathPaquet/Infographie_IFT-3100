#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxImGui.h"
#include "scene/sceneManager.h"
#include "Cursor.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void exit();

	SceneManager* sceneManager;
    ofxImGui::Gui gui;
	ofEasyCam camera;
	Cursor cursor = Cursor(CursorType::DRAWING);
    ImVec4 backgroundColor;

private:
	void drawSceneElementMenu();
	void drawSceneTopMenu();
	void createFileMenu();
	void createViewMenu();
};

