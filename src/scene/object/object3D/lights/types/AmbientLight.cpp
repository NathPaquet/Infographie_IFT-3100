#include "AmbientLight.h"

#include "ofLight.h"

AmbientLight::AmbientLight() {
  color.set(127, 127, 127);
  update();
}

void AmbientLight::toggle() {
  isEnableStatus = !isEnableStatus;
  update();
}

bool AmbientLight::isEnable() const {
  return this->isEnableStatus;
}

void AmbientLight::update() {
  ofSetGlobalAmbientColor(isEnableStatus ? color : ofColor::black);
}
