#pragma once

#include "WindowCamera.h"
#include "imgui.h"
#include "sceneManager.h"

class CameraPanel {
public:
  CameraPanel(SceneManager *sceneManager, WindowCamera *windowCamera);
  void create();

private:
  SceneManager *sceneManager;
  WindowCamera *windowCamera;
};
