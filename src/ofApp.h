#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxImGui.h"
#include "raycasting/ray.h"
#include "scene/sceneManager.h"
#include "Cursor.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void exit();

	glm::highp_vec3 findMouseClick3DPosition();

	SceneManager* sceneManager;
	ofxImGui::Gui gui;
	ofEasyCam camera;
	Cursor cursor = Cursor(CursorType::DRAWING);
    ImVec4 backgroundColor;
	Ray ray;

private:
	void drawSceneElementMenu();
	void drawSceneTopMenu();
	void createFileMenu();
	void createViewMenu();
};
