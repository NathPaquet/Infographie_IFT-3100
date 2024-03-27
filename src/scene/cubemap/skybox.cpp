#include "skybox.h"

void Skybox::loadTexture(const string &texturePath) {
  this->cubemapTexture.loadCubemapTextures(texturePath);
}

void Skybox::draw() {
  ofPushMatrix();

  ofTranslate(0, 0, 0);

  for (int i = 0; i < 6; ++i) {
    cubemapTexture.getCubemapTexture(i).bind();
    ofDrawBox(0, 0, 0, 2000, 2000, 2000);
    cubemapTexture.getCubemapTexture(i).unbind();
  }

  ofPopMatrix();
}
