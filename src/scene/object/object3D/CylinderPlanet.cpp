#include "CylinderPlanet.h"

#include "ImageImporter.h"

CylinderPlanet::CylinderPlanet(const float x, const float y, const float z) {
  SceneObject();
  this->addProperty<float>(PROPERTY_ID::HEIGHT, 20.f);
  this->addProperty<float>(PROPERTY_ID::RADIUS, 20.f);
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

void CylinderPlanet::updateProperties() {
  SceneObject::updateProperties();
  if (this->properties.at(PROPERTY_ID::HEIGHT)->isValueChanged() || this->properties.at(PROPERTY_ID::RADIUS)->isValueChanged()) {
    this->updatePrimitive();
    this->properties.at(PROPERTY_ID::HEIGHT)->setChanged(false);
    this->properties.at(PROPERTY_ID::RADIUS)->setChanged(false);
  }
}

void CylinderPlanet::updatePrimitive() {
  const float radius = this->getPropertyValue<float>(PROPERTY_ID::RADIUS);
  const float height = this->getPropertyValue<float>(PROPERTY_ID::HEIGHT);
  auto cylinder = ofCylinderPrimitive(radius, height, 20, 20, 20, true, OF_PRIMITIVE_TRIANGLES);
  this->primitive.reset(nullptr);
  this->primitive = std::make_unique<ofCylinderPrimitive>(std::move(cylinder));
  this->primitive->setGlobalPosition(position.x, position.y, position.z);
}
