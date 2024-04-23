#pragma once
#include "object/object3D/lights/Light.h"

class PointLight : public Light {
public:
  PointLight(const glm::vec3 &position);
};
