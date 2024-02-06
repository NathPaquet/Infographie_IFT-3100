#include "ofApp.h"
#include "of3dUtils.h"
#include "ImHelpers.h"
#include "scene/Planet.h"
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowTitle("BasedEngine");
	ofSetLogLevel(OF_LOG_VERBOSE);

	//required call
	gui.setup(nullptr, true, ImGuiConfigFlags_ViewportsEnable);

	//Initialize scene manager
	sceneManager = new SceneManager();

	//Initialize camera
	camera.setDistance(200.f);
	this->ray = Ray();
    //backgroundColor is stored as an ImVec4 type but can handle ofColor
    backgroundColor = ofColor(114, 144, 154);
}

//--------------------------------------------------------------
void ofApp::exit() {
	gui.exit();
}

glm::highp_vec3 ofApp::findMouseClick3DPosition(){
	glm::vec3 screenMouse (ofGetMouseX(),ofGetMouseY(),0);
	auto worldMouse = camera.screenToWorld(screenMouse);
	auto worldMouseEnd = camera.screenToWorld(glm::vec3(screenMouse.x, screenMouse.y, 1.0f));
	auto worldMouseDirection = worldMouseEnd - worldMouse;
	return glm::normalize(worldMouseDirection);
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
	ofDrawCircle(0, 0, 72);
	sceneManager->drawScene();

    gui.begin();
	
	auto worldMouseDirection = findMouseClick3DPosition();
	this->ray.set(camera.getGlobalPosition(), worldMouseDirection);

	//drawing showcase
	float radius = 10.f;
	this->ray.draw(radius);
	if(ImGui::IsMouseReleased(ImGuiMouseButton_Left)){
		sceneManager->addElement(ray.getOrigin() + ray.getDirection() * radius * 10.f);
	}
	
	camera.end();

	// Draw scene element menu
	drawSceneElementMenu();

	// Draw scene top menu
	drawSceneTopMenu();

	gui.end();
}

void ofApp::drawSceneElementMenu()
{
	ImGui::SetNextWindowPos(ImVec2(ofGetWindowPositionX(), ofGetWindowPositionY()), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(200, ofGetHeight()), ImGuiCond_Always);

	if (ImGui::Begin("Scene Element", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
	{
		if (ImGui::Button("Add Element", ImVec2(180, 30)))
		{
			ofLogNotice() << "Add Element button pressed";
		}

		if (ImGui::Button("Remove Element", ImVec2(180, 30)))
		{
			ofLogNotice() << "Remove Element button pressed";
		}
		ImGui::End();
	}
}

void ofApp::drawSceneTopMenu()
{
	ImGui::SetNextWindowPos(ImVec2(ofGetWindowPositionX() + 200, ofGetWindowPositionY()), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(ofGetWidth() - 200, ofGetHeight()), ImGuiCond_Always);

	ImGui::PushStyleColor(ImGuiCol_MenuBarBg, (ImVec4)ImColor(51, 56, 68, 255)); //Set the color of the menu bar

	if (ImGui::Begin("Menu bar", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground)) {
		if (ImGui::BeginMenuBar())
		{
			createFileMenu();
			createViewMenu();

			ImGui::EndMenuBar();
		}
		ImGui::End();
	}

	ImGui::PopStyleColor();
}

void ofApp::createFileMenu()
{
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("New"))
		{
			ofLogNotice() << "New button pressed";
		}
		if (ImGui::MenuItem("Open", "Ctrl+O"))
		{
			ofLogNotice() << "Open button pressed";
		}
		if (ImGui::MenuItem("Save", "Ctrl+S"))
		{
			ofLogNotice() << "Save button pressed";
		}
		if (ImGui::MenuItem("Save As.."))
		{
			ofLogNotice() << "Save As button pressed";
		}
		if (ImGui::MenuItem("Exit"))
		{
			ofLogNotice() << "Exit button pressed";
		}
		ImGui::EndMenu();
	}
}

void ofApp::createViewMenu()
{
	if (ImGui::BeginMenu("View"))
	{
		if (ImGui::MenuItem("3D Scene"))
		{
			ofLogNotice() << "3D Scene button pressed";
		}
		if (ImGui::MenuItem("2D Scene"))
		{
			ofLogNotice() << "2D Scene button pressed";
		}
		ImGui::EndMenu();
	}
}
