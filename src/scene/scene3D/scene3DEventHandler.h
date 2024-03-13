#pragma once
#include "scene3D.h"

class Scene3DEventHandler {
public:
  Scene3DEventHandler(Scene3D *scene3D):
      scene3D(scene3D) {}
  ~Scene3DEventHandler();
  void activateHandler();
  void deactivateHandler();

private:
  Scene3D *scene3D;
  bool isActivated = false;

  bool isMouseClickInScene() const;
  void mouseMoved(ofMouseEventArgs &mouseArgs);
};
