#pragma once

#include "object/object3D/Camera.h"
#include "ofMain.h"
#include "sceneManager.h"

class WindowCamera {
public:
  WindowCamera(SceneManager *sceneManager);
  void setSelectedCamera(Camera *camera);
  void drawScene();
  void switchIsShown();
  void setIsShown(bool isShown);

private:
  bool hasASelectedCamera() const;

  SceneManager *sceneManager;
  Camera *selectedCamera = nullptr;
  bool isShown = false;
};
