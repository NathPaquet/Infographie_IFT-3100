#pragma once
#include "AbstractPropertyDrawer.h"
#include "utils/Filtering.h"

class ImagePropertyDrawer : public AbstractPropertyDrawer {
public:
  void draw(std::vector<PropertyBase *> &objectsProperty) override;

private:
  void drawImport(const std::vector<PropertyBase *> &objectsProperty);
};
