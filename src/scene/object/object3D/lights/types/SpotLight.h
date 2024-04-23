#pragma once
#include "object/object3D/lights/Light.h"

class SpotLight : public Light {
public:
  SpotLight(const glm::vec3 &position);
};
