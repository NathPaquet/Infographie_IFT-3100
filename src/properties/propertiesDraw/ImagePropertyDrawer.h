#pragma once
#include "AbstractPropertyDrawer.h"
#include "utils/Filtering.h"

class ImagePropertyDrawer : public AbstractPropertyDrawer {
public:
  void draw(std::vector<PropertyBase *> &objectsProperty) override;

private:
  Filtering filtering;
  bool hasBlur = false;
  bool hasSharpen = false;
  bool hasGrey = false;

  void drawImport(const std::vector<PropertyBase *> &objectsProperty);
  void drawFiltering(const std::vector<PropertyBase *> &objectsProperty);
};
