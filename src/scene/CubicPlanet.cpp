#include "CubicPlanet.h"

void CubicPlanet::draw_properties() {
}

CubicPlanet::CubicPlanet(const float x, const float y, const float z) {
  auto box = ofBoxPrimitive(this->size, this->size, this->size);
  this->mainMesh = box.getMesh();
  for (int side = 0; side < 6; side++) {
    box.setSideColor(side, ofColor::fromHsb(ofRandom(255), 255, 255));
  }
  ofDisableArbTex();
  this->mTex.enableMipmap();
  this->mTex.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  this->mTex.generateMipmap();

  this->primitive = std::make_unique<ofBoxPrimitive>(std::move(box));
  this->primitive->setGlobalPosition(x, y, z);
  this->position = ofVec3f(x, y, z);
}
