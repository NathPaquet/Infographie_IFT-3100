#pragma once

#include "Cursor.h"
#include "eventListener/scene2DEventListener.h"
#include "eventListener/scene3DEventListener.h"
#include "eventListener/sceneEventListener.h"
#include "layouts/Tools.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxImGui.h"
#include "properties/PropertiesPanel.h"
#include "raycasting/ray.h"
#include "scene/scene.h"
#include "scene/scene2D.h"
#include "scene/scene3D.h"
#include "scene/sceneGraph.h"
#include "scene/sceneManager.h"

class ofApp : public ofBaseApp {
public:
  void setup();
  void draw();
  void exit();

  ofxImGui::Gui gui;

  ofImage backgroundImage;
  ofTexture backgroundTexture;

private:
  Tools tools;
  void drawPropertiesPanel();
  void drawSceneObjectGraph();
  void drawSceneObjectGraphCreationMenu();
  void drawSceneTopMenu();
  void createViewMenu();
  void generateRandomGalaxy(int nbElements);

  std::unique_ptr<SceneGraph> sceneGraph;
  std::unique_ptr<PropertiesPanel> propertiesPanel;
  std::unique_ptr<Scene> scene3D;
  std::unique_ptr<Scene> scene2D;
  std::unique_ptr<Cursor> cursor;
  bool isScene2D = false;
  Scene *currentScene;
};
