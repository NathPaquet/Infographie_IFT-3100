#pragma once
#include "cubemap.h"
#include "ofMain.h"

class Skybox {
public:
  Skybox();
  void loadTexture(const string &texturePath);
  void draw(const float &size, const glm::vec3 &cameraPosition) const;
  bool isSkyboxLoaded();
  bool isEnabled() const;
  const unsigned int getTextureObjectID() const;
  void toggleSkyboxActivation();

private:
  bool isSkyboxEnabled{true};
  bool isCubemapLoaded{false};
  Cubemap cubemapTexture;
  ofShader skyboxShader;
};
