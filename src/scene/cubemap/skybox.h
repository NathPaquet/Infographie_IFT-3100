#pragma once
#include "cubemap.h"
#include "ofMain.h"

class Skybox {
public:
  void loadTexture(const string &texturePath);
  void draw();

private:
  Cubemap cubemapTexture;
};
