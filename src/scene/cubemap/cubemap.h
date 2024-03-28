#pragma once
#include "ofMain.h"

class Cubemap {
public:
  void loadCubemapTextures(const string &cubemapTexturePath);
  const unsigned int getTextureObjectID() const;
  void bind() const;
  void unbind() const;

private:
  void uploadToCubemap(GLenum face, ofImage &image);

  ofImage right, left, top, bottom, front, back;
  unsigned int cubemapTextureObjectID;
};
