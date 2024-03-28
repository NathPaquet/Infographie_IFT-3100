#pragma once
#include "cubemap.h"
#include "ofMain.h"

class Skybox {
public:
  Skybox();
  void loadTexture(const string &texturePath);
  void draw(float size);

private:
  Cubemap cubemapTexture;
  ofShader skyboxShader;
};
