#include "cubemap.h"

void Cubemap::loadCubemapTextures(const string &cubemapTexturePath) {
  // Load cubemap textures
  // Order: right, left, top, bottom, front, back
  // x+ x- y+ y- z+ z-
  string textureNames[6] = {
      "right.png",
      "left.png",
      "top.png",
      "bottom.png",
      "front.png",
      "back.png"};

  ofDisableArbTex();

  for (int i = 0; i < 6; i++) {
    ofLoadImage(this->cubemapTextures[i], cubemapTexturePath + textureNames[i]);
    this->cubemapTextures[i].enableMipmap();
    this->cubemapTextures[i].setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    this->cubemapTextures[i].generateMipmap();
  }
  ofEnableArbTex();
}

const ofTexture &Cubemap::getCubemapTexture(int index) const {
  return this->cubemapTextures[index];
}
