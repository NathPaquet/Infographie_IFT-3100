#pragma once
#include "AbstractPropertyDrawer.h"

#include <textures/TexturePicker.h>

class TexturePropertyDrawer : public AbstractPropertyDrawer {
public:
  void draw(std::vector<PropertyBase *> &objectsProperty) override;

private:
  TexturePicker texturePicker;
};
