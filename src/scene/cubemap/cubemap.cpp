#include "cubemap.h"

void Cubemap::loadCubemapTextures(const string &cubemapTexturePath) {
  // Load cubemap textures
  // Order: right, left, top, bottom, front, back
  // x+ x- y+ y- z+ z-
  bool image1 = this->right.loadImage(cubemapTexturePath + "right.png");
  bool image2 = this->left.loadImage(cubemapTexturePath + "left.png");
  bool image3 = this->top.loadImage(cubemapTexturePath + "top.png");
  bool image4 = this->bottom.loadImage(cubemapTexturePath + "bot.png");
  bool image5 = this->front.loadImage(cubemapTexturePath + "front.png");
  bool image6 = this->back.loadImage(cubemapTexturePath + "back.png");

  if (!image1 || !image2 || !image3 || !image4 || !image5 || !image6) {
    ofLogError("Cubemap") << "Failed to load cubemap textures";
    return;
  }

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

  // glGenerateMipmap(GL_TEXTURE_CUBE_MAP_ARB);
}

void Cubemap::uploadToCubemap(GLenum face, ofImage &image) {
  glTexImage2D(face, 0, GL_RGB, image.getWidth(), image.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.getPixels().getData());
}

unsigned int Cubemap::getTextureObjectID() {
  return this->cubemapTextureObjectID;
}

void Cubemap::bind() {
  glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, this->cubemapTextureObjectID);
}

void Cubemap::unbind() {
  glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, 0);
}
