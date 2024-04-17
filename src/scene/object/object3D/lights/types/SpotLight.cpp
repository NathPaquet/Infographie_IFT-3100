#include "SpotLight.h"

SpotLight::SpotLight(const glm::vec3 &position):
    Light(position) {
  light.setSpotlight();
}
