#pragma once
#include "AbstractPropertyDrawer.h"
class ImagePropertyDrawer : public AbstractPropertyDrawer {
public:
  void draw(std::vector<PropertyBase *> &objectsProperty) override;
};
