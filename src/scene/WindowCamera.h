#pragma once

#include "object/object3D/Camera.h"
#include "ofMain.h"
#include "sceneManager.h"

class WindowCamera {
public:
  WindowCamera(SceneManager *sceneManager);
  void setSelectedCamera(Camera *camera);
  void draw();
  void setIsShown(bool isShown);

private:
  const float CAMERA_RADIUS = 2.f;
  const float CAMERA_LINE_LENGTH = 5.f;

  SceneManager *sceneManager;
  Camera *selectedCamera;
  bool isShown = false;
};
