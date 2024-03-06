#pragma once

#include "SceneManager.h"
#include "object/object3D/Camera.h"
#include "ofMain.h"

class WindowCamera {
public:
  WindowCamera(SceneManager *sceneManager);
  void draw();
  void setIsShown(bool isShown);

private:
  const float CAMERA_RADIUS = 2.f;
  const float CAMERA_LINE_LENGTH = 5.f;

  SceneManager *sceneManager;
  std::unique_ptr<Camera> selectedCamera;
  bool isShown = false;
};
