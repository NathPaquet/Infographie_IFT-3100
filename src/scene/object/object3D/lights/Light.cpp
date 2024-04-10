#include "Light.h"

#include "Constants.h"

Light::Light(const glm::vec3 &position) {
  this->addProperty<float>(PROPERTY_ID::RADIUS, Constants::DEFAULT_SIZE);

  auto sphere = ofSpherePrimitive(initialPrimitiveRadius, 20, OF_PRIMITIVE_TRIANGLES);
  this->primitive = std::make_unique<ofSpherePrimitive>(sphere);

  setPosition(position);
  light.enable();
}

void Light::updateProperties() {
  Object3D::updateProperties();
  updateLight();
}

void Light::updateLight() {
  if (this->properties.at(PROPERTY_ID::RADIUS)->isValueChanged()) {
    const float radius = this->getPropertyValue<float>(PROPERTY_ID::RADIUS);
    const float scale = getScale(radius);

    this->primitive.get()->setScale(scale); // this->setSize(radius);
    this->properties.at(PROPERTY_ID::RADIUS)->setChanged(false);

    light.setScale(scale);
  }

  auto &color = this->getPropertyValue<ofColor>(PROPERTY_ID::COLOR);
  if (this->properties.at(PROPERTY_ID::COLOR)->isValueChanged()) {
    light.setDiffuseColor(color);
  }

  auto &position = this->primitive.get()->getPosition();
  light.setPosition(position);

  auto &orientation = this->primitive.get()->getOrientationQuat();
  light.setOrientation(orientation);

  ofPushStyle();
  ofSetColor(color);
  light.draw();
  ofPopStyle();
}

float Light::getScale(float radius) const {
  return radius / Constants::DEFAULT_SIZE;
}
