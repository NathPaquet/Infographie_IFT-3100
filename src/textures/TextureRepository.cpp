#include "TextureRepository.h"

static std::list<std::unique_ptr<TexturePack>> textures;

void TextureRepository::addTexture(const std::string &packName) {
  textures.push_back(std::make_unique<TexturePack>(packName));
}

void TextureRepository::addTextureFromSingleImage(const ofImage &image, const std::string &id) {
  textures.push_back(std::make_unique<TexturePack>(image, id));
}

const std::list<std::unique_ptr<TexturePack>> &TextureRepository::getTextures() {
  return textures;
}

void TextureRepository::configureTextureWithShader(const std::string &id, std::shared_ptr<ofShader> shader) {
  auto it = std::find_if(textures.begin(), textures.end(), [&](auto &&element) { return element->packId == id; });
  it->get()->configureMaterial(shader);
}

const TexturePack *TextureRepository::getTexture(const std::string &packId) {
  auto it = std::find_if(getTextures().begin(), getTextures().end(), [&](auto &&element) { return element->packId == packId; });
  if (it == getTextures().end()) {
    return nullptr;
  }
  return it->get();
}

void TextureRepository::setTextureDiffuseMap(std::function<void(ofTexture &)> callback, const std::string &id) {
  auto it = std::find_if(textures.begin(), textures.end(), [&](auto &&element) { return element->packId == id; });
  callback(it->get()->textureDiffuseMap);
}
