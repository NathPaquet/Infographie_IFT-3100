#pragma once
#include "Property.h"
#include "ofColor.h"
#include "sceneObject.h"

class PropertiesPanel {
public:
  PropertiesPanel();
  void drawFloatProperty(std::vector<PropertyBase *> &objectsProperty);
  void drawColorProperty(std::vector<PropertyBase *> &objectsProperty);
  void drawImageImport(std::vector<PropertyBase *> &objectsProperty);
  void drawAngles(std::vector<PropertyBase *> &objectsProperty);
  void drawPropertiesPanel(std::vector<SceneObject *> &objects);

  static const float MIN_FLOAT_VALUE;
  static const float MAX_FLOAT_VALUE;
  static const float MIN_ANGLE_VALUE;
  static const float MAX_ANGLE_VALUE;

private:
  std::map<PROPERTY_ID, std::function<void(std::vector<PropertyBase *>)>> propertyDrawFunctions;
  std::map<PROPERTY_ID, std::vector<PropertyBase *>> findCommonProperties(const std::vector<SceneObject *> &objects);
  ColorPicker colorPicker;
};
