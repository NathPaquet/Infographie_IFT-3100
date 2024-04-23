#pragma once
#include "ofMain.h"

class Cubemap : public ofThread {
public:
  void threadedFunction() override;
  void setCubemapTexturePath(const string &cubemapTexturePath);
  bool enableCubemapTextures();
  const unsigned int getTextureObjectID() const;
  void setCubemapImage(const ofImage &right, const ofImage &left, const ofImage &top, const ofImage &bottom, const ofImage &front, const ofImage &back);

private:
  void uploadToCubemap(GLenum face, ofImage &image);

  bool isCubemapTextureLoaded = false;
  bool isCubemapTextureBinded = false;
  string cubemapTexturePath;
  ofImage right, left, top, bottom, front, back;
  unsigned int cubemapTextureObjectID;
};
