#include "CylinderPlanet.h"

#include "ImageImporter.h"
#include "constants.h"

CylinderPlanet::CylinderPlanet(const float x, const float y, const float z) {
  this->addProperty<float>(PROPERTY_ID::HEIGHT, Constants::DEFAULT_SIZE);
  this->addProperty<float>(PROPERTY_ID::RADIUS, Constants::DEFAULT_SIZE);
  const float height = this->getPropertyValue<float>(PROPERTY_ID::HEIGHT);
  const float radius = this->getPropertyValue<float>(PROPERTY_ID::RADIUS);

  auto cylinder = ofCylinderPrimitive(radius, height, 20, 20, 20, true, OF_PRIMITIVE_TRIANGLES);
  cylinder.setGlobalPosition(x, y, z);
  this->mainMesh = cylinder.getMesh();

  ofDisableArbTex();
  this->mTex.enableMipmap();
  this->mTex.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  this->mTex.generateMipmap();

  this->primitive = std::make_unique<ofCylinderPrimitive>(std::move(cylinder));
  this->primitive->setGlobalPosition(x, y, z);
  this->position = ofVec3f(x, y, z);
}

void CylinderPlanet::setSize(const float radius, const float height) {
  this->primitive.get()->setScale(radius / Constants::DEFAULT_SIZE, height / Constants::DEFAULT_SIZE, radius / Constants::DEFAULT_SIZE);
}

void CylinderPlanet::updateProperties() {
  Object3D::updateProperties();
  if (this->properties.at(PROPERTY_ID::HEIGHT)->isValueChanged() || this->properties.at(PROPERTY_ID::RADIUS)->isValueChanged()) {
    const float radius = this->getPropertyValue<float>(PROPERTY_ID::RADIUS);
    const float height = this->getPropertyValue<float>(PROPERTY_ID::HEIGHT);

    this->setSize(radius, height);
    this->properties.at(PROPERTY_ID::HEIGHT)->setChanged(false);
    this->properties.at(PROPERTY_ID::RADIUS)->setChanged(false);
  }
}
