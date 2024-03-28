#pragma once
#include "ofMain.h"

class Cubemap {
public:
  void loadCubemapTextures(const string &cubemapTexturePath);
  unsigned int getTextureObjectID();
  void bind();
  void unbind();

private:
  void uploadToCubemap(GLenum face, ofImage &image);

  ofImage right, left, top, bottom, front, back;
  unsigned int cubemapTextureObjectID;
};
