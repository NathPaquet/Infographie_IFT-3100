#include "PropertiesPanel.h"

#include "ImageImporter.h"
#include "imgui.h"

const float PropertiesPanel::MIN_FLOAT_VALUE = 0.0f;
const float PropertiesPanel::MAX_FLOAT_VALUE = 500.0f;

PropertiesPanel::PropertiesPanel() {
  auto floatDraw = [this](std::vector<PropertyBase *> &objectsProperty) { drawFloatProperty(objectsProperty); };
  auto imageImportDraw = [this](std::vector<PropertyBase *> &objectsProperty) { drawImageImport(objectsProperty); };
  auto colorDraw = [this](std::vector<PropertyBase *> &objectsProperty) { drawColorProperty(objectsProperty); };

  propertyDrawFunctions.emplace(PROPERTY_ID::SIZE, floatDraw);
  propertyDrawFunctions.emplace(PROPERTY_ID::RADIUS, floatDraw);
  propertyDrawFunctions.emplace(PROPERTY_ID::HEIGHT, floatDraw);

  propertyDrawFunctions.emplace(PROPERTY_ID::COLOR, colorDraw);
  propertyDrawFunctions.emplace(PROPERTY_ID::IMAGE_IMPORT, imageImportDraw);
}

void PropertiesPanel::drawFloatProperty(std::vector<PropertyBase *> &objectsProperty) {
  auto firstObjectProperty = dynamic_cast<Property<float> *>(objectsProperty[0]);
  auto propertyValue = firstObjectProperty->getValue();

  if (ImGui::SliderFloat(toString(firstObjectProperty->getId()), &propertyValue, MIN_FLOAT_VALUE, MAX_FLOAT_VALUE, NULL)) { // Returns true if the value was changed
    for (auto &&objectProperty : objectsProperty) {
      auto property = dynamic_cast<Property<float> *>(objectProperty);
      property->setValue(propertyValue);
    }
  }
}

void PropertiesPanel::drawColorProperty(std::vector<PropertyBase *> &objectsProperty) {
  auto firstObjectProperty = dynamic_cast<Property<ofColor> *>(objectsProperty[0]);
  auto propertyValue = firstObjectProperty->getValue();

  if (this->colorPicker.createColorPicker(propertyValue)) { // Returns true if the value was changed
    for (auto &&objectProperty : objectsProperty) {
      auto property = dynamic_cast<Property<ofColor> *>(objectProperty);
      property->setValue(propertyValue);
    }
  }
}

void PropertiesPanel::drawImageImport(std::vector<PropertyBase *> &objectsProperty) {
  if (ImGui::Button("Import image", ImVec2(100.f, 30.f))) { // Returns true if the button was pressed
    ImageImporter::importImage(objectsProperty);
  }
  if (ImGui::Button("Remove image", ImVec2(100.f, 30.f))) { // Returns true if the button was pressed
    for (auto &&objectProperty : objectsProperty) {
      auto property = dynamic_cast<Property<ofImage> *>(objectProperty);
      property->getValue().clear();
      property->setChanged(true);
    }
  }
}

void PropertiesPanel::drawPropertiesPanel(std::vector<SceneObject *> &objects) {
  if (objects.empty()) {
    return;
  }

  auto commonProperties = findCommonProperties(objects);

  for (auto &&property : commonProperties) {
    this->propertyDrawFunctions.at(property.first)(property.second);
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
