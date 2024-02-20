#pragma once
#include "Property.h"
#include "ofColor.h"
#include "sceneObject.h"

class PropertiesPanel {
public:
  void drawFloat(Property<float> *property);
  void drawColorProperty(Property<ofColor> &color);

  void drawPanel(std::vector<SceneObject *> &objects);
};
