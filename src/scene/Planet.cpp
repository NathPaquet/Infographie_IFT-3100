#include "Planet.h"

#include "CylinderPlanet.h"
#include "ImHelpers.h"
#include "ofxImGui.h"

Planet::Planet(const float x, const float y, const float z) {
  SceneObject();
  this->addProperty<float>(PROPERTY_ID::RADIUS, 20.f);

  auto sphere = ofSpherePrimitive(this->getPropertyValue<float>(PROPERTY_ID::RADIUS), 20, OF_PRIMITIVE_TRIANGLES);
  this->mainMesh = sphere.getMesh();

  ofDisableArbTex();
  this->mTex.enableMipmap();
  this->mTex.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  this->mTex.generateMipmap();

  this->primitive = std::make_unique<ofSpherePrimitive>(std::move(sphere));
  this->primitive->setGlobalPosition(x, y, z);
  this->position = ofVec3f(x, y, z);
}

void Planet::updateProperties() {
  SceneObject::updateProperties();
  if (this->properties.at(PROPERTY_ID::RADIUS)->isValueChanged()) {
    this->updatePrimitive();
    this->properties.at(PROPERTY_ID::RADIUS)->setChanged(false);
  }
}
void Planet::updatePrimitive() {
  auto sphere = ofSpherePrimitive(this->getPropertyValue<float>(PROPERTY_ID::RADIUS), 20, OF_PRIMITIVE_TRIANGLES);
  this->primitive.reset(nullptr);
  this->primitive = std::make_unique<ofSpherePrimitive>(std::move(sphere));
  this->primitive->setGlobalPosition(position.x, position.y, position.z);
}
