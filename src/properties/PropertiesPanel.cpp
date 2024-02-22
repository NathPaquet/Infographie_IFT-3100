#include "PropertiesPanel.h"

#include "ImageImporter.h"
#include "imgui.h"

const float PropertiesPanel::MIN_FLOAT_VALUE = 0.0f;
const float PropertiesPanel::MAX_FLOAT_VALUE = 500.0f;
const float PropertiesPanel::MIN_ANGLE_VALUE = 0.0f;
const float PropertiesPanel::MAX_ANGLE_VALUE = 360.0f;

PropertiesPanel::PropertiesPanel() {
  auto floatDraw = [this](std::vector<PropertyBase *> &objectsProperty) { drawFloatProperty(objectsProperty); };
  auto imageImportDraw = [this](std::vector<PropertyBase *> &objectsProperty) { drawImageImport(objectsProperty); };
  auto colorDraw = [this](std::vector<PropertyBase *> &objectsProperty) { drawColorProperty(objectsProperty); };
  auto anglesDraw = [this](std::vector<PropertyBase *> &objectsProperty) { drawAngles(objectsProperty); };

  propertyDrawFunctions.emplace(PROPERTY_ID::SIZE, floatDraw);
  propertyDrawFunctions.emplace(PROPERTY_ID::RADIUS, floatDraw);
  propertyDrawFunctions.emplace(PROPERTY_ID::HEIGHT, floatDraw);

  propertyDrawFunctions.emplace(PROPERTY_ID::COLOR, colorDraw);
  propertyDrawFunctions.emplace(PROPERTY_ID::IMAGE_IMPORT, imageImportDraw);

  propertyDrawFunctions.emplace(PROPERTY_ID::ANGLES, anglesDraw);
}

void PropertiesPanel::drawFloatProperty(std::vector<PropertyBase *> &objectsProperty) {
  auto firstObjectProperty = dynamic_cast<Property<float> *>(objectsProperty[0]);
  auto propertyValue = firstObjectProperty->getValue();

  ImGui::SeparatorText(toString(firstObjectProperty->getId()));

  if (ImGui::SliderFloat(toString(firstObjectProperty->getId()), &propertyValue, MIN_FLOAT_VALUE, MAX_FLOAT_VALUE, NULL, ImGuiSliderFlags_AlwaysClamp)) { // Returns true if the value was changed
    for (auto &&objectProperty : objectsProperty) {
      auto property = dynamic_cast<Property<float> *>(objectProperty);
      property->setValue(propertyValue);
    }
  }
  if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
    ImGui::SetItemTooltip("CTRL+Click to input value.");
}

void PropertiesPanel::drawColorProperty(std::vector<PropertyBase *> &objectsProperty) {
  auto firstObjectProperty = dynamic_cast<Property<ofColor> *>(objectsProperty[0]);
  auto propertyValue = firstObjectProperty->getValue();

  ImGui::SeparatorText(toString(firstObjectProperty->getId()));

  if (this->colorPicker.createColorPicker(propertyValue)) { // Returns true if the value was changed
    for (auto &&objectProperty : objectsProperty) {
      auto property = dynamic_cast<Property<ofColor> *>(objectProperty);
      property->setValue(propertyValue);
    }
  }
}

void PropertiesPanel::drawImageImport(std::vector<PropertyBase *> &objectsProperty) {
  auto firstObjectProperty = dynamic_cast<Property<ofImage> *>(objectsProperty[0]);
  ImGui::SeparatorText(toString(firstObjectProperty->getId()));

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

void PropertiesPanel::drawAngles(std::vector<PropertyBase *> &objectsProperty) {
  auto firstObjectProperty = dynamic_cast<Property<ofVec3f> *>(objectsProperty[0]);
  auto propertyValue = firstObjectProperty->getValue();

  ImGui::SeparatorText(toString(firstObjectProperty->getId()));
  bool angleXUsed = ImGui::SliderFloat("Angle X", &propertyValue.x, MIN_ANGLE_VALUE, MAX_ANGLE_VALUE, NULL, ImGuiSliderFlags_AlwaysClamp);
  if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
    ImGui::SetItemTooltip("CTRL+Click to input value.");
  bool angleYUsed = ImGui::SliderFloat("Angle Y", &propertyValue.y, MIN_ANGLE_VALUE, MAX_ANGLE_VALUE, NULL, ImGuiSliderFlags_AlwaysClamp);
  if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
    ImGui::SetItemTooltip("CTRL+Click to input value.");
  bool angleZUsed = ImGui::SliderFloat("Angle Z", &propertyValue.z, MIN_ANGLE_VALUE, MAX_ANGLE_VALUE, NULL, ImGuiSliderFlags_AlwaysClamp);
  if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
    ImGui::SetItemTooltip("CTRL+Click to input value.");

  if (angleXUsed || angleYUsed || angleZUsed) {
    for (auto &&objectProperty : objectsProperty) {
      auto property = dynamic_cast<Property<ofVec3f> *>(objectProperty);
      property->setValue(propertyValue);
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
