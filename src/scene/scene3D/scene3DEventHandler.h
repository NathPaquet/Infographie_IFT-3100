#pragma once
#include "scene3D.h"

class Scene3DEventHandler {
public:
  Scene3DEventHandler(Scene3D *scene3D):
      scene3D(scene3D) {}

private:
  Scene3D *scene3D;
};
