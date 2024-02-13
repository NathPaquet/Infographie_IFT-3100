#include "ofApp.h"

#include "ImHelpers.h"
#include "of3dUtils.h"
#include "scene/Planet.h"

#include <iostream>

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetWindowTitle("BasedEngine");
  ofSetLogLevel(OF_LOG_VERBOSE);
  ofDisableAlphaBlending();
  ofEnableDepthTest();
  // required call
  gui.setup(nullptr, true, ImGuiConfigFlags_ViewportsEnable);

  // Initialize scene manager
  sceneManager = new SceneManager();

  // Initialize camera
  camera.setDistance(200.f);
  this->light.setPosition(-500, 500, 500);
  this->light.enable();
  this->ray = Ray();
  // backgroundColor is stored as an ImVec4 type but can handle ofColor
  backgroundColor = ofColor(114, 144, 154);
}

//--------------------------------------------------------------
void ofApp::exit() {
  gui.exit();
}

glm::highp_vec3 ofApp::findMouseClick3DPosition() {
  glm::vec3 screenMouse(ofGetMouseX(), ofGetMouseY(), 0);
  auto worldMouse = camera.screenToWorld(screenMouse);
  auto worldMouseEnd = camera.screenToWorld(glm::vec3(screenMouse.x, screenMouse.y, 1.0f));
  auto worldMouseDirection = worldMouseEnd - worldMouse;
  return worldMouseDirection;
}

//--------------------------------------------------------------
void ofApp::update() {
  // ofSetCircleResolution(circleResolution);
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

  // drawing showcase
  float radius = 10.f;

  glm::vec2 baricentricCoordinates;
  float distance;
  bool found = false;
  float distanceToClosestIntersection = numeric_limits<float>::max();
  const SceneObject *foundSceneObject;
  ofColor color;
  for (auto &&object : this->sceneManager->getObjects()) {
    bool intersects = ray.isRayCollidingWithPrimitive(object.get()->getPrimitive(), baricentricCoordinates, distance);
    color = ofColor(240, 233, 233);
    if (intersects && (distance < distanceToClosestIntersection)) {
      found = true;
      foundSceneObject = object.get();
      distanceToClosestIntersection = distance;
    }
  }
  if (!found) {
    this->ray.draw(radius, color);
  }

  if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && isMouseClickInScene()) {
    if (found) {
      sceneManager->setSelectedSceneObject(foundSceneObject);
    } else {
      sceneManager->addElement(ray.getOrigin() + ray.getDirection() * radius * 10.f);
    }
  }

  camera.end();

  // Draw properties panel menu
  drawPropertiesPanel();

  // Draw scene element menu
  drawSceneElementMenu();

  // Draw scene top menu
  drawSceneTopMenu();
  gui.end();
}

void ofApp::drawSphere() {
  const float du = PI / 30;
  const float dv = PI / 30;
  const float r = 500.f;    // Radius of the sphere
  const float scale = 0.1f; // Scale factor for noise
  const float coeff = 0.5f; // Coefficient for noise

  for (float u = 0; u < 2 * PI; u += du) {
    for (float v = -PI / 2; v < PI / 2; v += dv) {
      vector<glm::vec3> vertices;
      for (int i = 0; i < 4; i++) {
        float uu = i == 0 || i == 3 ? u : u + du;
        float vv = i == 0 || i == 1 ? v : v + dv;
        vertices.push_back(position(uu, vv, r, scale, coeff));
      }
      ofSetColor(255); // Set color to white (you can change the color as needed)
      ofDrawTriangle(vertices[0], vertices[1], vertices[2]);
      ofDrawTriangle(vertices[0], vertices[2], vertices[3]);
    }
  }
}

//--------------------------------------------------------------
glm::vec3 ofApp::position(float u, float v, float r, float scale, float coeff) {
  // Calculate sphere point
  float x = r * cos(v) * cos(u);
  float y = r * cos(v) * sin(u);
  float z = r * sin(v);

  // Noise value at this point on sphere
  float offset = ofNoise(x * scale, y * scale, z * scale);

  // Apply noise to sphere point
  return glm::vec3(x * (1 + coeff * offset), y * (1 + coeff * offset), z * (1 + coeff * offset));
}

void ofApp::drawPropertiesPanel() {
  float window_width = 200.f;
  ImGui::SetNextWindowPos(ImVec2(ofGetWindowPositionX() + ofGetWidth() - window_width, ofGetWindowPositionY()), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(window_width, ofGetHeight()), ImGuiCond_Always);
  if (ImGui::Begin("PropertiesPanel", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse)) {
    this->sceneManager->drawPropertiesPanel();
    ImGui::End();
  }
}

bool ofApp::isMouseClickInScene() {
  return ofGetMouseX() > 200 && ofGetMouseX() < ofGetWidth() - 200;
}

void ofApp::drawSceneElementMenu() {
  ImGui::SetNextWindowPos(ImVec2(ofGetWindowPositionX(), ofGetWindowPositionY()), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(200, ofGetHeight()), ImGuiCond_Always);

  if (ImGui::Begin("Scene Element", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse)) {
    if (ImGui::Button("Add Element", ImVec2(180, 30))) {
      ofLogNotice() << "Add Element button pressed";
    }

    if (ImGui::Button("Remove Element", ImVec2(180, 30))) {
      ofLogNotice() << "Remove Element button pressed";
    }

    ImGui::End();
  }
}

void ofApp::drawSceneTopMenu() {
  ImGui::SetNextWindowPos(ImVec2(ofGetWindowPositionX() + 200, ofGetWindowPositionY()), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(ofGetWidth() - 200 * 2, ofGetHeight()), ImGuiCond_Always);

  ImGui::PushStyleColor(ImGuiCol_MenuBarBg, (ImVec4)ImColor(51, 56, 68, 255)); // Set the color of the menu bar

  if (ImGui::Begin("Menu bar", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground)) {
    if (ImGui::BeginMenuBar()) {
      createFileMenu();
      createViewMenu();
      tools.createToolsMenu();

      ImGui::EndMenuBar();
    }
    ImGui::End();
  }

  ImGui::PopStyleColor();
}

void ofApp::createFileMenu() {
  if (ImGui::BeginMenu("File")) {
    if (ImGui::MenuItem("New")) {
      ofLogNotice() << "New button pressed";
    }
    if (ImGui::MenuItem("Open", "Ctrl+O")) {
      ofLogNotice() << "Open button pressed";
    }
    if (ImGui::MenuItem("Save", "Ctrl+S")) {
      ofLogNotice() << "Save button pressed";
    }
    if (ImGui::MenuItem("Save As..")) {
      ofLogNotice() << "Save As button pressed";
    }
    if (ImGui::MenuItem("Exit")) {
      ofLogNotice() << "Exit button pressed";
    }
    ImGui::EndMenu();
  }
}

void ofApp::createViewMenu() {
  if (ImGui::BeginMenu("View")) {
    if (ImGui::MenuItem("3D Scene")) {
      ofLogNotice() << "3D Scene button pressed";
    }
    if (ImGui::MenuItem("2D Scene")) {
      ofLogNotice() << "2D Scene button pressed";
    }
    ImGui::EndMenu();
  }
}

void ofApp::mouseReleased(int x, int y, int button) {
  // float radius = 10.f;

  // if (button == 0) // Left mouse button
  //{
  //	sceneManager->addElement(ray.getOrigin() + ray.getDirection() * radius * 10.f);
  // }
}
