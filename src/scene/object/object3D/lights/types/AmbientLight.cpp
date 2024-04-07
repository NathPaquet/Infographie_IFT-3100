#include "AmbientLight.h"

#include "ofLight.h"

AmbientLight::AmbientLight(const ofColor &color) {
  this->color = color;
  update();
}

void AmbientLight::toggle() {
  isOn = !isOn;
  update();
}

void AmbientLight::update() {
  if (isOn) {
    ofSetGlobalAmbientColor(color);
  } else {
    ofSetGlobalAmbientColor(ofColor::black);
  }
}
