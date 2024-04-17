#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::vec3 &position):
    Light(position) {
  light.setDirectional();
}
