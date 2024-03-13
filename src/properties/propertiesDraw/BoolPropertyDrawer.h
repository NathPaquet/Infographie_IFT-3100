#pragma once
#include "AbstractPropertyDrawer.h"
class BoolPropertyDrawer : public AbstractPropertyDrawer {
public:
  void draw(std::vector<PropertyBase *> &objectsProperty) override;

private:
};
