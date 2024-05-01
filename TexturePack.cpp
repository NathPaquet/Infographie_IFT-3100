#include "TexturePack.h"

TexturePack::TexturePack(const ofImage &image, const std::string &id) {
  loadSingleImage(image, id);
}

TexturePack::TexturePack(const std::string &packName) {
  load(packName);
}

void TexturePack::loadSingleImage(const ofImage &image, const std::string &id) {
  this->packId = id;
  textureDiffuseMap = image.getTexture();
  if (textureDiffuseMap.isAllocated()) {
    configureTexture(textureDiffuseMap);
  }
  // loading default values i.e a texture filled with 0 for displacement and normal mapping:

  ofPixels pixels;
  pixels.allocate(1024, 1024, OF_PIXELS_RGBA);
  pixels.setColor(ofColor(0, 0, 0, 255));
  textureNormalMap.loadData(pixels);
  textureAORoughMetal.loadData(pixels);
  textureDisplacementMap.loadData(pixels);

  configureTexture(textureNormalMap);
  configureTexture(textureAORoughMetal);
  configureTexture(textureDisplacementMap);
}

bool TexturePack::load(const std::string &packName) {
  this->packId = packName;
  std::string filename = ofToLower(packName);
  std::map<std::string, ofTexture *> textureNames = {{"_diff", &textureDiffuseMap},
      {"_nor_gl", &textureNormalMap},
      {"_disp", &textureDisplacementMap},
      {"_arm", &textureAORoughMetal}};

  std::array<std::string, 2> extension = {"png", "jpg"};

  bool was_success = false;
  for (auto &&texture : textureNames) {
    for (auto &&ext : extension) {
      was_success = ofLoadImage(*texture.second, "textures/" + packName + "/" + filename + texture.first + "." + ext);
      if (was_success) {
        break;
      }
    }
    if (was_success) {
      configureTexture(*texture.second);
    }
  }

  return was_success;
}

void TexturePack::configureTexture(ofTexture &texture) {
  texture.setTextureWrap(GL_REPEAT, GL_REPEAT);
  texture.generateMipmap();

  GLfloat fLargest = 1.0;
  glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);

  texture.bind();
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  texture.unbind();
}

void TexturePack::configureMaterial(std::shared_ptr<ofShader> shader) {
  material.setCustomShader(shader);
  material.setAmbientColor(ofFloatColor(1, 1, 1, 0.6));
  // set our textures on the material so that they will be passed to our custom shader
  material.setCustomUniformTexture("mapDiffuse", textureDiffuseMap, 0);
  material.setCustomUniformTexture("mapNormal", textureNormalMap, 1);
  material.setCustomUniformTexture("mapDisplacement", textureDisplacementMap, 2);
  material.setCustomUniformTexture("mapAORoughMetal", textureAORoughMetal, 3);
  material.setCustomUniform1f("matRoughness", 0.5f);
  material.setCustomUniform1f("matOcclusion", 1.f);

  setDisplacementStrength(2.f);
  material.setCustomUniform1f("matMetallic", 0.5f);
  material.setCustomUniform1f("matRoughness", 0.5f);
  material.setCustomUniform1f("matOcclusion", 1.f);
}

void TexturePack::setMetallicity(float metallicity) {
  material.setCustomUniform1f("matMetallic", metallicity);
  this->metallic = metallicity;
}

void TexturePack::setDisplacementStrength(float displacementStrength) {
  material.setCustomUniform1f("matDisplacementStrength", displacementStrength);
  this->displacementStrength = displacementStrength;
}

void TexturePack::setDisplacementTexture(const ofTexture &displacementTexture) {
  textureDisplacementMap = displacementTexture;
  configureTexture(textureDisplacementMap);
  material.setCustomUniformTexture("mapDisplacement", textureDisplacementMap, 2);
}

void TexturePack::setRoughness(float roughness) {
  material.setCustomUniform1f("matRoughness", roughness);
  this->roughness = roughness;
}

float TexturePack::getMetallicity() const {
  return metallic;
}

float TexturePack::getRoughness() const {
  return roughness;
}

float TexturePack::getDisplacementStrength() const {
  return displacementStrength;
}
