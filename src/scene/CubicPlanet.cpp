#include "CubicPlanet.h"

#include "ImageImporter.h"
#include "properties/Property.h"

CubicPlanet::CubicPlanet(const float x, const float y, const float z) {
  SceneObject();
  this->addProperty<float>(PROPERTY_ID::SIZE, 20.f);

  float size = this->getPropertyValue<float>(PROPERTY_ID::SIZE);
  auto box = ofBoxPrimitive(size, size, size);

  ofDisableArbTex();
  this->mTex.enableMipmap();
  this->mTex.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  this->mTex.generateMipmap();

  this->primitive = std::make_unique<ofBoxPrimitive>(std::move(box));
  this->primitive->setGlobalPosition(x, y, z);
  this->position = ofVec3f(x, y, z);
}

void CubicPlanet::updateProperties() {
  SceneObject::updateProperties();
  if (this->properties.at(PROPERTY_ID::SIZE)->isValueChanged()) {
    this->set_size(this->getPropertyValue<float>(PROPERTY_ID::SIZE));
    this->properties.at(PROPERTY_ID::SIZE)->setChanged(false);
  }
}

void CubicPlanet::set_size(const float size) {
  auto box = ofBoxPrimitive(size, size, size);
  this->primitive.reset(nullptr);
  this->primitive = std::make_unique<ofBoxPrimitive>(std::move(box));
  this->primitive->setGlobalPosition(position.x, position.y, position.z);
}
