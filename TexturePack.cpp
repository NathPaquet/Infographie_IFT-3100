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
  // paramètres du matériau
  auto material_color_ambient = ofColor(63, 63, 63);
  auto material_color_diffuse = ofColor(255, 255, 255);
  auto material_color_specular = ofColor(255, 255, 255);

  float material_metallic = 0.5f;
  float material_roughness = 0.5f;
  float material_occlusion = 1.0f;
  float material_brightness = 1.0f;

  auto material_fresnel_ior = glm::vec3(0.04f, 0.04f, 0.04f);

  // paramètres de la lumière
  auto light_color = ofColor(255, 255, 255);
  float light_intensity = 1.0f;

  // paramètres de mappage tonal
  float tone_mapping_exposure = 1.0f;

  material.setCustomUniform3f("material_color_ambient", {material_color_ambient.r / 255.0f, material_color_ambient.g / 255.0f, material_color_ambient.b / 255.0f});
  material.setCustomUniform3f("material_color_diffuse", {material_color_diffuse.r / 255.0f, material_color_diffuse.g / 255.0f, material_color_diffuse.b / 255.0f});
  material.setCustomUniform3f("material_color_specular", {material_color_specular.r / 255.0f, material_color_specular.g / 255.0f, material_color_specular.b / 255.0f});

  material.setCustomUniform1f("material_brightness", material_brightness);
  setRoughness(material_roughness);
  setMetallicity(material_metallic);
  material.setCustomUniform1f("material_occlusion", material_occlusion);

  material.setCustomUniform3f("material_fresnel_ior", material_fresnel_ior);

  material.setCustomUniformTexture("texture_diffuse", textureDiffuseMap, 1);
  material.setCustomUniformTexture("texture_AORoughMetal", textureAORoughMetal, 2);
  material.setCustomUniformTexture("texture_displacement", textureDisplacementMap, 3);
  material.setCustomUniformTexture("texture_normal", textureNormalMap, 4);

  material.setCustomUniform1f("light_intensity", light_intensity);

  material.setCustomUniform1f("tone_mapping_exposure", tone_mapping_exposure);
  material.setCustomUniform1f("tone_mapping_gamma", 2.2f);

  setDisplacementStrength(2.f);
}

void TexturePack::setMetallicity(float metallicity) {
  material.setCustomUniform1f("material_metallic", metallicity);
  this->metallic = metallicity;
}

void TexturePack::setDisplacementStrength(float displacementStrength) {
  material.setCustomUniform1f("matDisplacementStrength", displacementStrength);
  this->displacementStrength = displacementStrength;
}

void TexturePack::setDisplacementTexture(const ofTexture &displacementTexture) {
  textureDisplacementMap = displacementTexture;
  configureTexture(textureDisplacementMap);
  material.setCustomUniformTexture("texture_displacement", textureDisplacementMap, 3);
}

void TexturePack::setRoughness(float roughness) {
  material.setCustomUniform1f("material_roughness", roughness);
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
