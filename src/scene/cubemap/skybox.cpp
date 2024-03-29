#include "skybox.h"

#include "constants.h"
#include "utils/loadingScreen.h"

Skybox::Skybox() {
  this->skyboxShader.load("shaders/skybox.vert", "shaders/skybox.frag");
  this->cubemapTexture.setCubemapTexturePath(Constants::CUBEMAP_TEXTURE_SKYBOX_LIGHTBLUE);
  this->cubemapTexture.startThread();
}

void Skybox::loadTexture(const string &texturePath) {
  this->cubemapTexture.setCubemapTexturePath(texturePath);
  this->cubemapTexture.startThread();
}

void Skybox::draw(const float &size, const glm::vec3 &cameraPosition) {
  if (this->cubemapTexture.enableCubemapTextures()) {
    skyboxShader.begin();
    skyboxShader.setUniform1i("skybox", 0);

    ofDisableDepthTest();

    ofDrawBox(cameraPosition.x, cameraPosition.y, cameraPosition.z, size);

    ofEnableDepthTest();

    skyboxShader.end();
  } else {
    string message = "Skybox texture not loaded yet";
    LoadingScreen::drawLoadingScreen(message);
  }
}
