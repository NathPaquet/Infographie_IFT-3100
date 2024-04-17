#pragma once

#include "Cursor.h"
#include "layouts/CameraPanel.h"
#include "layouts/Tools.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxImGui.h"
#include "properties/PropertiesPanel.h"
#include "raycasting/ray.h"
#include "scene/scene.h"
#include "scene/scene2D/scene2D.h"
#include "scene/scene3D/scene3D.h"
#include "scene/sceneGraph.h"
#include "scene/sceneManager.h"
#include "scene2D/scene2DEventHandler.h"
#include "scene3D/scene3DEventHandler.h"

class ofApp : public ofBaseApp {
public:
  void setup();
  void draw();
  void update();
  void exit();

  ofxImGui::Gui gui;

  ofImage backgroundImage;
  ofTexture backgroundTexture;

private:
  void drawPropertiesPanel();
  void drawSceneObjectGraph();
  void drawSceneObjectGraphCreationMenu();
  void drawSceneTopMenu();
  void createViewMenu();
  void toggleSkyboxFor3DScene();
  void createSkyboxTopMenu();
  void updateKeyboardShortcuts();
  void generateRandomGalaxy(int nbElements);
  void generateCornellBox(float size);
  void switchBetweenScenes();
  void switchBetweenProjections();
  Tools tools;
  std::unique_ptr<CameraPanel> cameraPanel;
  std::unique_ptr<WindowCamera> windowCamera;

  std::unique_ptr<SceneGraph> sceneGraph;
  std::unique_ptr<PropertiesPanel> propertiesPanel;
  std::unique_ptr<Scene3D> scene3D;
  std::unique_ptr<Scene3DEventHandler> scene3DEventHandler;
  std::unique_ptr<Scene2D> scene2D;
  std::unique_ptr<Scene2DEventHandler> scene2DEventHandler;
  std::unique_ptr<Cursor> cursor;

  bool isScene2D = false;
  bool isViewOrtho = false;
  bool isSkyboxEnabled{true};
  bool isBoundingBoxEnabled = false;
  bool isObjectAxisEnabled = false;
  Scene *currentScene;
};
