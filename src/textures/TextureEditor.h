#pragma once
#include "TexturePicker.h"

enum class TextureType {
  DIFFUSE,
  NORMAL,
  DISPLACEMENT,
  AO_ROUGH_METAL
};

class TextureEditor {
public:
  void displayEditorOptions();
  void displayGenericOptions();
  void displayTextureSpecificOptions(const TexturePack *texture);
  void generateDisplacementMapForTexture(const TexturePack *texture);
  void drawTextureEditor();
  void setCurrentTexture(const TexturePack *texture);
  void drawImages(const TexturePack *texture);

private:
  TexturePicker texturePicker;
  const TexturePack *currentTexture{nullptr};

  bool hasBlur{false};
  bool hasSharpen{false};
  bool hasGrey{false};
};
