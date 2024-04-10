#pragma once

#include "object/object3D/Camera.h"
#include "ofMain.h"
#include "scene3D/scene3D.h"

class WindowCamera {
public:
  WindowCamera(Scene3D *scene);
  void setSelectedCamera(Camera *camera);
  Camera *getSelectedCamera() const;
  bool getIsShow() const;
  void drawScene();
  void switchIsShown();

private:
  bool hasNoSelectedCamera() const;

  const float RATIO_SCENE = 0.375f;
  Scene3D *scene;
  Camera *selectedCamera = nullptr;
  bool isShown = false;
};
