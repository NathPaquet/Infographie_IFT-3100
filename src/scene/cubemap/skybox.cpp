#include "skybox.h"

Skybox::Skybox() {
  this->skyboxShader.load("shaders/skybox.vert", "shaders/skybox.frag");
}

void Skybox::loadTexture(const string &texturePath) {
  this->cubemapTexture.loadCubemapTextures(texturePath);
}

void Skybox::draw(float size) {
  skyboxShader.begin();
  skyboxShader.setUniform1i("skybox", 0);

  ofDisableDepthTest();

  ofDrawBox(0, 0, 0, size); // TODO : Position de la caméra

  ofEnableDepthTest();

  skyboxShader.end();
}
