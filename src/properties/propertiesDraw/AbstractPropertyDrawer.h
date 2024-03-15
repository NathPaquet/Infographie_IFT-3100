#pragma once
#include <Property.h>
#include <vector>

class AbstractPropertyDrawer {
public:
  void virtual draw(std::vector<PropertyBase *> &objectsProperty) = 0;
};
