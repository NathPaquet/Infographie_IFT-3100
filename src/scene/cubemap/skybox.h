#pragma once
#include "cubemap.h"
#include "ofMain.h"

class Skybox {
public:
  Skybox();
  void loadTexture(const string &texturePath);
  void draw(float size);

private:
  void drawSkybox(float x, float y, float z, float width, float height, float length);

  Cubemap cubemapTexture;
  ofShader skyboxShader;
};
