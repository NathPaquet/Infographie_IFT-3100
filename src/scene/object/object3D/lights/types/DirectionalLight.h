#pragma once
#include "object/object3D/lights/Light.h"

class DirectionalLight : public Light {
public:
  DirectionalLight(const glm::vec3 &position);
};
