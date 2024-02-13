#include "Planet.h"

#include "ImHelpers.h"
#include "ofxImGui.h"

void Planet::draw_properties() {
  float radius_temp = this->radius;

  if (ImGui::SliderFloat("Radius", &radius_temp, 0.f, 500.f, "sss")) {
    set_radius(radius_temp);
  }

  if (ImGui::Button("Import image", ImVec2(100.f, 30.f))) {
    ImageImporter::importImage(this->image);
    if (this->image.isAllocated()) {
      this->mTex = image.getTexture();
      this->mTex.enableMipmap();
      this->mTex.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
      this->mTex.generateMipmap();
    }
  }
  if (ImGui::Button("Remove image", ImVec2(100.f, 30.f))) {
    mTex.clear();
    image.clear();
  }

  colorPicker.createColorPicker();
}

Planet::Planet(const float x, const float y, const float z) {
  auto sphere = ofSpherePrimitive(this->radius, 20, OF_PRIMITIVE_TRIANGLES);
  this->mainMesh = sphere.getMesh();

  ofDisableArbTex();
  this->mTex.enableMipmap();
  this->mTex.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  this->mTex.generateMipmap();

  this->primitive = std::make_unique<ofSpherePrimitive>(std::move(sphere));
  this->primitive->setGlobalPosition(x, y, z);
  this->position = ofVec3f(x, y, z);
}

void Planet::set_radius(const float radius) {
  this->radius = radius;
  auto sphere = ofSpherePrimitive(this->radius, 20, OF_PRIMITIVE_TRIANGLES);
  this->primitive.reset(nullptr);
  this->primitive = std::make_unique<ofSpherePrimitive>(std::move(sphere));
  this->primitive->setGlobalPosition(position.x, position.y, position.z);
}
