#include "Planet.h"

#include "CylinderPlanet.h"
#include "ImHelpers.h"
#include "constants.h"
#include "ofxImGui.h"

Planet::Planet(const float x, const float y, const float z) {
  this->addProperty<float>(PROPERTY_ID::RADIUS, Constants::DEFAULT_SIZE);

  auto sphere = ofSpherePrimitive(this->getPropertyValue<float>(PROPERTY_ID::RADIUS), 20, OF_PRIMITIVE_TRIANGLES);
  this->mainMesh = sphere.getMesh();

  ofDisableArbTex();

  this->primitive = std::make_unique<ofSpherePrimitive>(std::move(sphere));
  this->primitive->setGlobalPosition(x, y, z);
  this->position = ofVec3f(x, y, z);
}

void Planet::updateProperties() {
  Object3D::updateProperties();
  if (this->properties.at(PROPERTY_ID::RADIUS)->isValueChanged()) {
    const float radius = this->getPropertyValue<float>(PROPERTY_ID::RADIUS);

    this->setSize(radius);
    this->properties.at(PROPERTY_ID::RADIUS)->setChanged(false);
  }
}
void Planet::setSize(const float radius) {
  this->primitive.get()->setScale(radius / Constants::DEFAULT_SIZE);
}
