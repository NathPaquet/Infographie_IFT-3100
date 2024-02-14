#include "CubicPlanet.h"

#include "ImageImporter.h"

void CubicPlanet::draw_properties() {
  SceneObject::draw_properties();
  float size_temp = this->size;

  if (ImGui::SliderFloat("Radius", &size_temp, 0.f, 500.f, "size")) {
    this->set_size(size_temp);
  }
}

CubicPlanet::CubicPlanet(const float x, const float y, const float z) {
  auto box = ofBoxPrimitive(this->size, this->size, this->size);
  this->mainMesh = box.getMesh();

  ofDisableArbTex();
  this->mTex.enableMipmap();
  this->mTex.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  this->mTex.generateMipmap();

  this->primitive = std::make_unique<ofBoxPrimitive>(std::move(box));
  this->primitive->setGlobalPosition(x, y, z);
  this->position = ofVec3f(x, y, z);
}

void CubicPlanet::set_size(const float size) {
  this->size = size;
  auto box = ofBoxPrimitive(this->size, this->size, this->size);
  this->primitive.reset(nullptr);
  this->primitive = std::make_unique<ofBoxPrimitive>(std::move(box));
  this->primitive->setGlobalPosition(position.x, position.y, position.z);
}
