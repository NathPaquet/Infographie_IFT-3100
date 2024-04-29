#pragma once
#include "TexturePicker.h"

class TextureEditor {
public:
  void drawTextureEditor();
  void setCurrentTexture(const TexturePack *texture);
  static void displayImage(const TexturePack *texture);

private:
  TexturePicker texturePicker;
  const TexturePack *currentTexture{nullptr};
};
