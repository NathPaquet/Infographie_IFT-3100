#include "ofApp.h"

#include "ImHelpers.h"
#include "of3dUtils.h"
#include "scene/Planet.h"
#include "scene/SceneElementFactory.h"

#include <iostream>

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetWindowTitle("BasedEngine");
  ofSetLogLevel(OF_LOG_VERBOSE);
  ofDisableAlphaBlending();
  ofEnableDepthTest();
  // required call
  gui.setup(nullptr, true, ImGuiConfigFlags_ViewportsEnable);
  sceneManager = new SceneManager();
  sceneGraph = new SceneGraph(*sceneManager);
  backgroundImage.load("background.jpg");

  ofDisableArbTex();
  backgroundTexture = backgroundImage.getTexture();
  backgroundTexture.enableMipmap();
  backgroundTexture.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  backgroundTexture.generateMipmap();

  sphere.enableTextures();
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

glm::highp_vec3 ofApp::findMouseClick3DPosition() const {
  const glm::vec3 screenMouse(ofGetMouseX(), ofGetMouseY(), 0);
  auto &&worldMouse = camera.screenToWorld(screenMouse);
  auto &&worldMouseEnd = camera.screenToWorld(glm::vec3(screenMouse.x, screenMouse.y, 1.0f));
  auto &&worldMouseDirection = worldMouseEnd - worldMouse;
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

  ofPushStyle();
  backgroundTexture.bind();
  sphere.draw();
  backgroundTexture.unbind();
  ofPopStyle();

  ofDrawCircle(0, 0, 72);
  sceneManager->drawScene();

  gui.begin();

  processMouseActions();

  camera.end();

  // Draw properties panel menu
  drawPropertiesPanel();

  // Draw scene element menu
  drawSceneElementMenu();

  // Draw scene top menu
  drawSceneTopMenu();
  gui.end();
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
    this->sceneGraph->drawSceneGraphElements();

    if (ImGui::Button("Add Sphere", ImVec2(180, 30))) {
      currentElementToAdd = ElementType::SPHERE;
      this->cursor.setCursorMode(CursorMode::ADDING);
    }

    if (ImGui::Button("Add Cube", ImVec2(180, 30))) {
      currentElementToAdd = ElementType::CUBIC;
      this->cursor.setCursorMode(CursorMode::ADDING);
    }

    if (ImGui::Button("Add Cylinder", ImVec2(180, 30))) {
      currentElementToAdd = ElementType::CYLINDER;
      this->cursor.setCursorMode(CursorMode::ADDING);
    }

    if (ImGui::Button("Remove Element", ImVec2(180, 30))) {
      this->cursor.setCursorMode(CursorMode::REMOVING);
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

void ofApp::processMouseActions() {
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
  if (!found && this->cursor.getCursorMode() == CursorMode::ADDING) {
    this->ray.drawPrimitivePreview(color, this->currentElementToAdd, 20.f);
  }

  if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && isMouseClickInScene()) {
    if (found && this->cursor.getCursorMode() == CursorMode::NAVIGATION) {
      sceneManager->setSelectedSceneObject(foundSceneObject);

    } else if (found && this->cursor.getCursorMode() == CursorMode::REMOVING) {
      sceneManager->removeElement(foundSceneObject);
      this->cursor.setCursorMode(CursorMode::NAVIGATION);

    } else if (this->cursor.getCursorMode() == CursorMode::ADDING) {
      sceneManager->addElement(ray.getOrigin() + ray.getDirection() * 20.f * 10.f, this->currentElementToAdd);
      this->cursor.setCursorMode(CursorMode::NAVIGATION);
      sceneManager->setSelectedSceneObject(sceneManager->getObjects().back().get());
    }
  }
}

void ofApp::mouseReleased(int x, int y, int button) {
}
