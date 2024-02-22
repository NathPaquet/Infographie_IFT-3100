#pragma once
#include "ofMain.h"
#include "properties/Property.h"

class ImageImporter {
public:
  static void importImage(std::vector<PropertyBase *> objectsProperty);
};
