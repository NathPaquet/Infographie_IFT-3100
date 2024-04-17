#pragma once
#include "cubemap.h"
#include "ofMain.h"

class Skybox {
public:
  Skybox();
  void loadTexture(const string &texturePath);
  void draw(const float &size, const glm::vec3 &cameraPosition);
  bool isSkyboxLoaded();
  const unsigned int getTextureObjectID() const;

private:
  bool isCubemapLoaded{false};
  Cubemap cubemapTexture;
  ofShader skyboxShader;
};
