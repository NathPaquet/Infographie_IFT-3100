#include "CylinderPlanet.h"

#include "ImageImporter.h"

void CylinderPlanet::draw_properties() {
  SceneObject::draw_properties();
  float radius_temp = this->radius;
  float height_temp = this->height;

  if (ImGui::SliderFloat("Radius", &radius_temp, 0.f, 500.f, "radius")) {
    setRadius(radius_temp);
  }

  if (ImGui::SliderFloat("Height", &height_temp, 0.f, 500.f, "height")) {
    setHeight(height_temp);
  }
}

CylinderPlanet::CylinderPlanet(const float x, const float y, const float z) {
  auto cylinder = ofCylinderPrimitive(this->radius, this->height, 20, 20, 20, true, OF_PRIMITIVE_TRIANGLES);
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

void CylinderPlanet::setHeight(const float height) {
  this->height = height;
  auto cylinder = ofCylinderPrimitive(this->radius, this->height, 20, 20, 20, true, OF_PRIMITIVE_TRIANGLES);
  this->primitive.reset(nullptr);
  this->primitive = std::make_unique<ofCylinderPrimitive>(std::move(cylinder));
  this->primitive->setGlobalPosition(position.x, position.y, position.z);
}

void CylinderPlanet::setRadius(const float radius) {
  this->radius = radius;
  auto cylinder = ofCylinderPrimitive(this->radius, this->height, 20, 20, 20, true, OF_PRIMITIVE_TRIANGLES);
  this->primitive.reset(nullptr);
  this->primitive = std::make_unique<ofCylinderPrimitive>(std::move(cylinder));
  this->primitive->setGlobalPosition(position.x, position.y, position.z);
}
