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

  glm::highp_vec3 findMouseClick3DPosition() const;

  SceneManager *sceneManager;
  ofxImGui::Gui gui;
  ofEasyCam camera;
  ofLight light;
  ofImage backgroundImage;
  ofTexture backgroundTexture;
  ofSpherePrimitive sphere = ofSpherePrimitive(20, 60, OF_PRIMITIVE_TRIANGLES);
  Cursor cursor = Cursor(CursorMode::NAVIGATION);
  ElementType currentElementToAdd;
  ImVec4 backgroundColor;
  Ray ray;

private:
  Tools tools;
  void drawPropertiesPanel();
  bool isMouseClickInScene();
  void drawSceneElementMenu();
  void drawSceneTopMenu();
  void createFileMenu();
  void createViewMenu();
  void processMouseActions();
};
