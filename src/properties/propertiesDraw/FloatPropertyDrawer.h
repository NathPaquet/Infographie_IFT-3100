#pragma once
#include "AbstractPropertyDrawer.h"

class FloatPropertyDrawer : public AbstractPropertyDrawer {
public:
  FloatPropertyDrawer(const float min, const float max);
  void draw(std::vector<PropertyBase *> &objectsProperty) override;

private:
  float min;
  float max;
};
