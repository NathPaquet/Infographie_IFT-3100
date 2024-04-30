#pragma once
#include "ofMain.h"

#include <string>

class TexturePack {
public:
  TexturePack() = default;
  TexturePack(const ofImage &image, const std::string &id);
  TexturePack(const std::string &packName);

  void loadSingleImage(const ofImage &image, const std::string &id);
  void setDiffuseMap(ofImage image);

  bool load(const std::string &packName);
  void configureTexture(ofTexture &texture);
  void configureMaterial(std::shared_ptr<ofShader> shader);

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
  ofPixels defaultPixels;

  bool hasBlur;
  bool hasSharpen;
  bool hasGrey;
};