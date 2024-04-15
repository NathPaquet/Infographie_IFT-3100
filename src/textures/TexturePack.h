#pragma once
#include "ofMain.h"

#include <string>

class TexturePack {
public:
  TexturePack() = default;
  TexturePack(const ofImage &image, const std::string &id) {
    loadSingleImage(image, id);
  }

  TexturePack(const std::string &packName) {
    load(packName);
  }

  void loadSingleImage(const ofImage &image, const std::string &id) {
    this->packId = id;
    textureDiffuseMap = image.getTexture();
    if (textureDiffuseMap.isAllocated()) {
      configureTexture(textureDiffuseMap);
    }
  }

  bool load(const std::string &packName) {
    this->packId = packName;
    std::string filename = ofToLower(packName);

    bool was_success = ofLoadImage(textureDiffuseMap, "textures/" + packName + "/" + filename + "_diff.jpg");
    was_success |= ofLoadImage(textureNormalMap, "textures/" + packName + "/" + filename + "_nor_gl.jpg");
    was_success |= ofLoadImage(textureDisplacementMap, "textures/" + packName + "/" + filename + "_disp.png");
    was_success |= ofLoadImage(textureAORoughMetal, "textures/" + packName + "/" + filename + "_arm.jpg");

    if (textureDiffuseMap.isAllocated()) {
      configureTexture(textureDiffuseMap);
    }
    if (textureNormalMap.isAllocated()) {
      configureTexture(textureNormalMap);
    }
    if (textureDisplacementMap.isAllocated()) {
      configureTexture(textureDisplacementMap);
    }
    if (textureAORoughMetal.isAllocated()) {
      configureTexture(textureAORoughMetal);
    }

    return was_success;
  };

  void configureTexture(ofTexture &texture) {
    texture.setTextureWrap(GL_REPEAT, GL_REPEAT);
    texture.generateMipmap();

    GLfloat fLargest = 1.0;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);

    texture.bind();
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    texture.unbind();

    texture.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  }

  void configureMaterial(std::shared_ptr<ofShader> shader) {
    material.setCustomShader(shader);
    material.setAmbientColor(ofFloatColor(1, 1, 1, 0.6));
    // set our textures on the material so that they will be passed to our custom shader
    material.setCustomUniformTexture("mapDiffuse", textureDiffuseMap, 0);
    material.setCustomUniformTexture("mapNormal", textureNormalMap, 1);
    material.setCustomUniformTexture("mapDisplacement", textureDisplacementMap, 2);
    material.setCustomUniformTexture("mapAORoughMetal", textureAORoughMetal, 3);
  }
  // diffuse texture map holds the color information
  ofTexture textureDiffuseMap;
  // texture holding the normal values for the mesh that will be used for lighting in the frag shader
  ofTexture textureNormalMap;
  // texture holding the values for how far to offset the mesh vertices in vertex shader
  ofTexture textureDisplacementMap;
  // texture holding ambient occlusion, roughness and metal properties
  // we will only be using the ambient occlusion value stored in the red channel
  ofTexture textureAORoughMetal;

  ofMaterial material;

  ofFloatColor baseColor;

  std::string packId;
};