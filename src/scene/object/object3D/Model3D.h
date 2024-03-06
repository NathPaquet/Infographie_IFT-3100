#pragma once
#include "object/sceneObject.h"

#include <ray.h>

class Model3D : public SceneObject {
public:
  Model3D(const glm::vec3 &position);
};
