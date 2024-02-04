#include "ofApp.h"
#include "ImHelpers.h"
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowTitle("BasedEngine");
	ofSetLogLevel(OF_LOG_VERBOSE);
    
    //required call
    gui.setup(nullptr, true, ImGuiConfigFlags_ViewportsEnable );

    //Initialize scene manager
    sceneManager = new SceneManager();

    //Initialize camera
	camera.setDistance(200.f);

    //backgroundColor is stored as an ImVec4 type but can handle ofColor
    backgroundColor = ofColor(114, 144, 154);
}

//--------------------------------------------------------------
void ofApp::exit() {
	gui.exit();
}

//--------------------------------------------------------------
void ofApp::update() {
	//ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void ofApp::draw() {
	cursor.drawCursor(ofGetMouseX(), ofGetMouseY());
	camera.begin();
	ofNoFill();
	ofDrawSphere(64);
	ofDrawCircle(0, 0, 72);
    sceneManager->drawScene();

	camera.end();

    gui.begin();
    // Show the ImGui test window. Most of the sample code is in ImGui::ShowDemoWindow()
    ImGui::SetNextWindowPos( ofVec2f( ofGetWindowPositionX(), ofGetWindowPositionY()), ImGuiCond_Once);
    ImGui::SetNextWindowSize( ofVec2f(ofGetWidth(), ofGetHeight()), ImGuiCond_Once);
    ImGui::Begin("Test !");

	if (ImGui::Button("Hello world", ImVec2(200.f, 200.f))){
		std::cout << "ahah" << std::endl;
	}
	
	ImGui::End();
	
    // Draw left menu (Scene Element)
    ImGui::SetNextWindowPos(ImVec2(ofGetWindowPositionX(), ofGetWindowPositionY()), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, ofGetHeight()), ImGuiCond_Always);
    ImGui::Begin("Scene Element", nullptr, ImGuiWindowFlags_NoMove);

    // Add your menu items here
    if (ImGui::Button("Add Element", ImVec2(180, 30))) {
        // Code to add element to the scene
    }

    if (ImGui::Button("Remove Element", ImVec2(180, 30))) {
        // Code to remove element from the scene
    }

    // Add more menu items as needed

    ImGui::End();



    //required to call this at end
    gui.end();
}
