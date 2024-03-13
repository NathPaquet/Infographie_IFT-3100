#include "PropertiesPanel.h"

#include "ImageImporter.h"
#include "imgui.h"

#include <propertiesDraw/BoolPropertyDrawer.h>
#include <propertiesDraw/ColorPropertyDrawer.h>
#include <propertiesDraw/FloatPropertyDrawer.h>
#include <propertiesDraw/ImagePropertyDrawer.h>

constexpr float MIN_FLOAT_VALUE = 0.0f;
constexpr float MAX_FLOAT_VALUE = 50.0f;
constexpr float MIN_ANGLE_VALUE = 0.0f;
constexpr float MAX_ANGLE_VALUE = 360.0f;

PropertiesPanel::PropertiesPanel() {
  propertyDrawFunctions.emplace(PROPERTY_ID::SIZE, std::make_unique<FloatPropertyDrawer>(MIN_FLOAT_VALUE, MAX_FLOAT_VALUE));
  propertyDrawFunctions.emplace(PROPERTY_ID::RADIUS, std::make_unique<FloatPropertyDrawer>(MIN_FLOAT_VALUE, MAX_FLOAT_VALUE));
  propertyDrawFunctions.emplace(PROPERTY_ID::HEIGHT, std::make_unique<FloatPropertyDrawer>(MIN_FLOAT_VALUE, MAX_FLOAT_VALUE));
  propertyDrawFunctions.emplace(PROPERTY_ID::WIDTH, std::make_unique<FloatPropertyDrawer>(MIN_FLOAT_VALUE, MAX_FLOAT_VALUE));
  propertyDrawFunctions.emplace(PROPERTY_ID::RATIO, std::make_unique<FloatPropertyDrawer>(MIN_FLOAT_VALUE, MAX_FLOAT_VALUE));

  propertyDrawFunctions.emplace(PROPERTY_ID::SHOW_WIREFRAME, std::make_unique<BoolPropertyDrawer>());
  propertyDrawFunctions.emplace(PROPERTY_ID::COLOR, std::make_unique<ColorPropertyDrawer>());
  propertyDrawFunctions.emplace(PROPERTY_ID::IMAGE_IMPORT, std::make_unique<ImagePropertyDrawer>());
  propertyDrawFunctions.emplace(PROPERTY_ID::ANGLE_X, std::make_unique<FloatPropertyDrawer>(MIN_ANGLE_VALUE, MAX_ANGLE_VALUE));
  propertyDrawFunctions.emplace(PROPERTY_ID::ANGLE_Y, std::make_unique<FloatPropertyDrawer>(MIN_ANGLE_VALUE, MAX_ANGLE_VALUE));
  propertyDrawFunctions.emplace(PROPERTY_ID::ANGLE_Z, std::make_unique<FloatPropertyDrawer>(MIN_ANGLE_VALUE, MAX_ANGLE_VALUE));
}

void PropertiesPanel::drawPropertiesPanel(std::vector<SceneObject *> &objects) {
  if (objects.empty()) {
    return;
  }

  auto commonProperties = findCommonProperties(objects);

  for (auto &&property : commonProperties) {
    this->propertyDrawFunctions.at(property.first)->draw(property.second);
  }
}

std::map<PROPERTY_ID, std::vector<PropertyBase *>> PropertiesPanel::findCommonProperties(const std::vector<SceneObject *> &objects) {
  std::map<PROPERTY_ID, std::vector<PropertyBase *>> commonProperties;

  if (objects.empty()) {
    return commonProperties;
  }

  for (auto &&property : objects[0]->getProperties()) {
    commonProperties[property.first].push_back(property.second.get());
  }

  for (size_t i = 1; i < objects.size(); ++i) {
    for (auto &&property : objects[i]->getProperties()) {
      auto it = commonProperties.find(property.first);
      if (it != commonProperties.end()) {
        commonProperties[property.first].push_back(property.second.get());
      }
    }
  }

  if (objects.size() > 1) {
    std::vector<PROPERTY_ID> keysToRemove;

    for (auto &&property : commonProperties) {
      if (property.second.size() != objects.size()) {
        keysToRemove.push_back(property.first);
      }
    }

    for (auto key : keysToRemove) {
      commonProperties.erase(key);
    }
  }

  return commonProperties;
}
