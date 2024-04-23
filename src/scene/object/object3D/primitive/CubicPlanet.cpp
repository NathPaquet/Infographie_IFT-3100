#include "CubicPlanet.h"

#include "ImageImporter.h"
#include "constants.h"
#include "properties/Property.h"

CubicPlanet::CubicPlanet(const float x, const float y, const float z) {
  this->addProperty<float>(PROPERTY_ID::SIZE, Constants::DEFAULT_SIZE);

  float size = this->getPropertyValue<float>(PROPERTY_ID::SIZE);

  this->primitive = std::make_unique<ofBoxPrimitive>(size, size, size);
  this->primitive->setGlobalPosition(x, y, z);
  this->position = ofVec3f(x, y, z);
}

CubicPlanet::CubicPlanet(const float x, const float y, const float z, float size) {
  this->addProperty<float>(PROPERTY_ID::SIZE, size);

  this->primitive = std::make_unique<ofBoxPrimitive>(size, size, size);
  this->primitive->setGlobalPosition(x, y, z);
  this->position = ofVec3f(x, y, z);
}

void CubicPlanet::updateProperties() {
  Object3D::updateProperties();
  if (this->properties.at(PROPERTY_ID::SIZE)->isValueChanged()) {
    this->set_size(this->getPropertyValue<float>(PROPERTY_ID::SIZE));
    this->properties.at(PROPERTY_ID::SIZE)->setChanged(false);
  }
}

void CubicPlanet::set_size(const float size) {
  this->primitive.get()->setScale(size / Constants::DEFAULT_SIZE);
}
