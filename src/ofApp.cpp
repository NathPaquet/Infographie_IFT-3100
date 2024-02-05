#include "ofApp.h"
#include "ImHelpers.h"
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowTitle("BasedEngine");
	ofSetLogLevel(OF_LOG_VERBOSE);

    //Initialize SceneMode;
    isScene3D = true;
    
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

    // Draw left menu (Scene Element Manager)
    ImGui::SetNextWindowPos(ImVec2(ofGetWindowPositionX(), ofGetWindowPositionY()), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, ofGetHeight()), ImGuiCond_Always);
    ImGui::Begin("Scene Element", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

    // Add your menu items here
    if (ImGui::Button("Add Element", ImVec2(180, 30))) {
        // Code to add element to the scene
    }

    if (ImGui::Button("Remove Element", ImVec2(180, 30))) {
        // Code to remove element from the scene
    }

    // Add more menu items as needed

    ImGui::End();

    //Draw the scene window
    ImGui::SetNextWindowPos(ImVec2(ofGetWindowPositionX() + 200, ofGetWindowPositionY()), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(ofGetWidth() - 200, ofGetHeight()), ImGuiCond_Always);
    ImGui::PushStyleColor(ImGuiCol_MenuBarBg, (ImVec4)ImColor(51, 56, 68, 255));
    ImGui::Begin("Dear ImGui Demo", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);
   
    ImGui::BeginMenuBar();
    if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("New")) {
            ofLogNotice() << "New button pressed";
			// Code to create a new scene
		}
        if (ImGui::MenuItem("Open", "Ctrl+O")) {
            ofLogNotice() << "Open button pressed";
			// Code to open a scene
		}
        if (ImGui::MenuItem("Save", "Ctrl+S")) {
            ofLogNotice() << "Save button pressed";
			// Code to save the scene
		}
        if (ImGui::MenuItem("Save As..")) {
            ofLogNotice() << "Save As button pressed";
			// Code to save the scene as a new file
		}
        if (ImGui::MenuItem("Exit")) {
            ofLogNotice() << "Exit button pressed";
			// Code to exit the application
		}
		ImGui::EndMenu();
	}

    if (ImGui::BeginMenu("View")) {
        if (ImGui::MenuItem("3D Scene")) {
			ofLogNotice() << "3D Scene button pressed";
			isScene3D = true;
		}
        if (ImGui::MenuItem("2D Scene")) {
			ofLogNotice() << "2D Scene button pressed";
			isScene3D = false;
		}
		ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
    ImGui::End();
    ImGui::PopStyleColor();




    //required to call this at end
    gui.end();
}
