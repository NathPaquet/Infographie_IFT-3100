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

    glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemapTexture.getTextureObjectID());

    ofDrawBox(cameraPosition.x, cameraPosition.y, cameraPosition.z, size);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    ofEnableDepthTest();

    skyboxShader.end();
  } else {
    string message = "Skybox texture not loaded yet";
    LoadingScreen::drawLoadingScreen(message);
  }
}

const unsigned int Skybox::getTextureObjectID() const {
  return this->cubemapTexture.getTextureObjectID();
}
