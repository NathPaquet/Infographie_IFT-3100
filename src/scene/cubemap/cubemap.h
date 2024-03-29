#pragma once
#include "ofMain.h"

class Cubemap : public ofThread {
public:
  void threadedFunction() override;
  void setCubemapTexturePath(const string &cubemapTexturePath);
  bool enableCubemapTextures();
  const unsigned int getTextureObjectID() const;
  void bind() const;
  void unbind() const;

private:
  void uploadToCubemap(GLenum face, ofImage &image);

  bool isCubemapTextureLoaded = false;
  bool isCubemapTextureBinded = false;
  string cubemapTexturePath;
  ofImage right, left, top, bottom, front, back;
  unsigned int cubemapTextureObjectID;
};
