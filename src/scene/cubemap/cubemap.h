#pragma once
#include "ofMain.h"

class Cubemap {
public:
  void loadCubemapTextures(const string &cubemapTexturePath);
  const ofTexture &getCubemapTexture(int index) const;

private:
  ofTexture cubemapTextures[6];
};
