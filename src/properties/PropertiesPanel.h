#pragma once
#include "Property.h"
#include "object/sceneObject.h"
#include "ofColor.h"
#include "propertiesDraw/AbstractPropertyDrawer.h"

class PropertiesPanel {
public:
  PropertiesPanel();
  void drawPropertiesPanel(std::vector<SceneObject *> &objects);

private:
  std::map<PROPERTY_ID, std::unique_ptr<AbstractPropertyDrawer>> propertyDrawFunctions;
  std::map<PROPERTY_ID, std::vector<PropertyBase *>> findCommonProperties(const std::vector<SceneObject *> &objects);
};
