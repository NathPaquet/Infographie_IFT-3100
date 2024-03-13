#pragma once

#include "object/object3D/Camera.h"
#include "ofMain.h"
#include "sceneManager.h"

class WindowCamera {
public:
  WindowCamera(SceneManager *sceneManager);
  void setSelectedCamera(Camera *camera);
  Camera *getSelectedCamera() const;
  void drawScene();
  void switchIsShown();
  void setIsShown(bool isShown);

private:
  bool hasNoSelectedCamera() const;

  const float RATIO_SCENE = 0.375f;
  SceneManager *sceneManager;
  Camera *selectedCamera = nullptr;
  bool isShown = false;
};
