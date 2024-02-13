#include "Planet.h"

#include "ImHelpers.h"
#include "ofxImGui.h"

void Planet::draw() const {
  ofPushStyle();
  if (mTex.isAllocated()) {
    mTex.bind();
    primitive->draw();
    mTex.unbind();
  } else {
    ofSetColor(colorPicker.getNormalizedColor());
    primitive->draw();
  }
  ofPopStyle();
}

void Planet::draw_properties() {
  float radius_temp = this->radius;
  if (ImGui::Button("+##dasdasdasdas", ImVec2(50.f, 50.f))) {
    set_radius(this->radius + 20);
  }
  if (ImGui::Button("-", ImVec2(50.f, 50.f))) {
    set_radius(this->radius - 20);
  }
  if (ImGui::SliderFloat("Radius", &radius_temp, 0.f, 500.f, "sss")) {
    set_radius(radius_temp);
  }

  colorPicker.createColorPicker();
}

Planet::Planet(const float x, const float y, const float z) {
  auto sphere = ofSpherePrimitive(this->radius, 20, OF_PRIMITIVE_TRIANGLES);
  this->mainMesh = sphere.getMesh();
  // for (int side =0; side < 6; side++){
  //     box.setSideColor(side , ofColor::fromHsb(ofRandom(255), 255, 255));
  // }
  ofDisableArbTex();
  mTex.enableMipmap();
  ofLoadImage(mTex, "earth.jpg");
  mTex.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

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
