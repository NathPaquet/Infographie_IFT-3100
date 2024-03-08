#pragma once

#include "WindowCamera.h"
#include "imgui.h"
#include "sceneManager.h"

class CameraPanel {
public:
  CameraPanel(SceneManager *sceneManager, WindowCamera *windowCamera);
  void setSceneManager(SceneManager *sceneManager);
  void create();

private:
  SceneManager *sceneManager;
  WindowCamera *windowCamera;
  bool isWindowCameraShown = false;
};
