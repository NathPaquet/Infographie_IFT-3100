#include "skybox.h"

Skybox::Skybox() {
  this->skyboxShader.load("shaders/skybox.vert", "shaders/skybox.frag");
}

void Skybox::loadTexture(const string &texturePath) {
  this->cubemapTexture.loadCubemapTextures(texturePath);
}

void Skybox::draw(const float &size, const glm::vec3 &cameraPosition) const {
  skyboxShader.begin();
  skyboxShader.setUniform1i("skybox", 0);

  ofDisableDepthTest();

  ofDrawBox(cameraPosition.x, cameraPosition.y, cameraPosition.z, size);

  ofEnableDepthTest();

  skyboxShader.end();
}
