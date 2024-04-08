#include "Light.h"

#include "Constants.h"

Light::Light(const glm::vec3 &position) {
  this->addProperty<float>(PROPERTY_ID::RADIUS, Constants::DEFAULT_SIZE);

  auto sphere = ofSpherePrimitive(20.f, 20, OF_PRIMITIVE_TRIANGLES);
  this->primitive = std::make_unique<ofSpherePrimitive>(sphere);

  setPosition(position);
  light.enable();
}

void Light::updateProperties() {
  Object3D::updateProperties();
  updateLight();
}

void Light::updateLight() {
  auto &color = this->getPropertyValue<ofColor>(PROPERTY_ID::COLOR);
  light.setDiffuseColor(color);

  auto &position = this->primitive.get()->getPosition();
  light.setPosition(position);

  auto &orientation = this->primitive.get()->getOrientationQuat();
  light.setOrientation(orientation);
}
