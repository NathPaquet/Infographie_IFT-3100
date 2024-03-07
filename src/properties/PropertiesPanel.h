#pragma once
#include "Property.h"
#include "object/sceneObject.h"
#include "ofColor.h"

class PropertiesPanel {
public:
  PropertiesPanel();
  void drawFloatProperty(std::vector<PropertyBase *> &objectsProperty);
  void drawColorProperty(std::vector<PropertyBase *> &objectsProperty);
  void drawImageImport(std::vector<PropertyBase *> &objectsProperty);
  void drawAngles(std::vector<PropertyBase *> &objectsProperty);
  void drawToggle(std::vector<PropertyBase *> &objectsProperty);
  void drawPropertiesPanel(std::vector<SceneObject *> &objects);

private:
  std::map<PROPERTY_ID, std::function<void(std::vector<PropertyBase *>)>> propertyDrawFunctions;
  std::map<PROPERTY_ID, std::vector<PropertyBase *>> findCommonProperties(const std::vector<SceneObject *> &objects);
  ColorPicker colorPicker;
};
