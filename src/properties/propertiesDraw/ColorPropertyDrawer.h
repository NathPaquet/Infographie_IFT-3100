#pragma once
#include "AbstractPropertyDrawer.h"

#include <ColorPicker.h>
class ColorPropertyDrawer : public AbstractPropertyDrawer {
public:
  void draw(std::vector<PropertyBase *> &objectsProperty) override;

private:
  ColorPicker colorPicker;
};
