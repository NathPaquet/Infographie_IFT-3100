#pragma once
#include "TexturePack.h"

#include <memory>
#include <vector>

class TextureRepository {
public:
  static void addTexture(const std::string &packName);
  static void addTextureFromSingleImage(const ofImage &image, const std::string &id);
  static const std::list<std::unique_ptr<TexturePack>> &getTextures();
  static void configureTextureWithShader(const std::string &id, std::shared_ptr<ofShader> shader);
  static const TexturePack *getTexture(const std::string &packId);
};