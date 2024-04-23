#include "Light.h"

#include "Constants.h"

Light::Light(const glm::vec3 &position) {
  this->addProperty<float>(PROPERTY_ID::RADIUS, Constants::DEFAULT_SIZE);

  auto sphere = ofSpherePrimitive(initialPrimitiveRadius, 20, OF_PRIMITIVE_TRIANGLES);
  this->primitive = std::make_unique<ofSpherePrimitive>(sphere);

  auto &color = this->getPropertyValue<ofColor>(PROPERTY_ID::COLOR);
  light.setDiffuseColor(color);
  setPosition(position);
  light.enable();
}

Light::~Light() {
  light.disable();
}

void Light::updateProperties() {
  updateLight();
  Object3D::updateProperties();
}

void Light::updateLight() {
  if (this->properties.at(PROPERTY_ID::RADIUS)->isValueChanged()) {
    const float radius = this->getPropertyValue<float>(PROPERTY_ID::RADIUS);
    const float scale = getScale(radius);

    this->primitive.get()->setScale(scale);
    this->properties.at(PROPERTY_ID::RADIUS)->setChanged(false);

    light.setScale(scale);
  }

  if (this->properties.at(PROPERTY_ID::COLOR)->isValueChanged()) {
    auto &color = this->getPropertyValue<ofColor>(PROPERTY_ID::COLOR);
    light.setDiffuseColor(color);
    // DO NOT set changed to false because 3dObject have to update the color too
  }

  auto &position = this->primitive.get()->getPosition();
  light.setPosition(position);

  auto &orientation = this->primitive.get()->getOrientationQuat();
  light.setOrientation(orientation);
}

void Light::draw(bool isSelected, bool isBoundingBoxEnable, bool isObjectAxisEnable) const {
  ofPushStyle();
  ofSetColor(this->getPropertyValue<ofColor>(PROPERTY_ID::COLOR));
  light.draw();
  ofPopStyle();
}

float Light::getScale(float radius) const {
  return radius / Constants::DEFAULT_SIZE;
}
