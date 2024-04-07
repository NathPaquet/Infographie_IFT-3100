#include "PointLight.h"

PointLight::PointLight(const glm::vec3 &position):
    Light(position) {
  light.setPointLight();
}
