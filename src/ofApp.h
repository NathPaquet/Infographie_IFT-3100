#pragma once

#include "Cursor.h"
#include "layouts/Tools.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxImGui.h"
#include "raycasting/ray.h"
#include "scene/sceneManager.h"

class ofApp : public ofBaseApp {
public:
  void setup();
  void update();
  void draw();
  void exit();

  void mouseReleased(int x, int y, int button);

  glm::highp_vec3 findMouseClick3DPosition();

  SceneManager *sceneManager;
  ofxImGui::Gui gui;
  ofEasyCam camera;
  ofLight light;
  Cursor cursor = Cursor(CursorType::DRAWING);
  ImVec4 backgroundColor;
  Ray ray;

private:
  Tools tools;
  void drawSphere();
  glm::vec3 position(float u, float v, float r, float scale, float coeff);
  void drawPropertiesPanel();
  bool isMouseClickInScene();
  void drawSceneElementMenu();
  void drawSceneTopMenu();
  void createFileMenu();
  void createViewMenu();
};
