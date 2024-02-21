#pragma once
#include "Property.h"
#include "ofColor.h"
#include "sceneObject.h"

class PropertiesPanel {
public:
  PropertiesPanel();
  void drawFloatProperty(Property<float> *property);
  void drawColorProperty(Property<ofColor> *property);
  void drawImageImport(Property<ofImage> *property);
  void drawAngles(Property<ofVec3f> *property);
  void drawPanel(std::vector<SceneObject *> &objects);

private:
  std::map<PROPERTY_ID, std::function<void(PropertyBase *)>> propertyDrawFunctions;
  ColorPicker colorPicker;
};
