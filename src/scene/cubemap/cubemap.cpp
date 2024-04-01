#include "cubemap.h"

void Cubemap::threadedFunction() {
  bool image1 = this->right.load(cubemapTexturePath + "right.png");
  bool image2 = this->left.load(cubemapTexturePath + "left.png");
  bool image3 = this->top.load(cubemapTexturePath + "top.png");
  bool image4 = this->bottom.load(cubemapTexturePath + "bot.png");
  bool image5 = this->front.load(cubemapTexturePath + "front.png");
  bool image6 = this->back.load(cubemapTexturePath + "back.png");

  if (!image1 || !image2 || !image3 || !image4 || !image5 || !image6) {
    ofLogError("Cubemap") << "Failed to load cubemap textures";
    return;
  } else {
    this->isCubemapTextureLoaded = true;
  }
}

void Cubemap::setCubemapTexturePath(const string &cubemapTexturePath) {
  if (this->cubemapTexturePath != cubemapTexturePath) {
    glDeleteTextures(1, &this->cubemapTextureObjectID);
    this->cubemapTexturePath = cubemapTexturePath;
    this->isCubemapTextureLoaded = false;
    this->isCubemapTextureBinded = false;
  }
}

bool Cubemap::enableCubemapTextures() {
  if (!this->isCubemapTextureBinded && this->isCubemapTextureLoaded) {
    // Load cubemap textures
    // Order: right, left, top, bottom, front, back
    //         x+     x-    y+    y-      z+    z-
    glGenTextures(1, &this->cubemapTextureObjectID);
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, this->cubemapTextureObjectID);

    uploadToCubemap(GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB, right);
    uploadToCubemap(GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB, left);
    uploadToCubemap(GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB, top);
    uploadToCubemap(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB, bottom);
    uploadToCubemap(GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB, front);
    uploadToCubemap(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB, back);

    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    this->isCubemapTextureBinded = true;
    return true;
  } else if (this->isCubemapTextureBinded && this->isCubemapTextureLoaded) {
    return true;
  } else {
    return false;
  }
}

void Cubemap::uploadToCubemap(GLenum face, ofImage &image) {
  glTexImage2D(face, 0, GL_RGB, image.getWidth(), image.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.getPixels().getData());
}

const unsigned int Cubemap::getTextureObjectID() const {
  return this->cubemapTextureObjectID;
}
