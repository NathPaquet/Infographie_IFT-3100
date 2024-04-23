#include "AmbientLight.h"

#include "ofLight.h"

AmbientLight::AmbientLight() {
  color.set(127, 127, 127);
}

void AmbientLight::toggle() {
  isEnableStatus = !isEnableStatus;
  update();
}

bool AmbientLight::isEnable() const {
  return this->isEnableStatus;
}

void AmbientLight::update() {
  if (isEnableStatus) {
    ofSetGlobalAmbientColor(color);
  } else {
    ofSetGlobalAmbientColor(ofColor::black);
  }
}
