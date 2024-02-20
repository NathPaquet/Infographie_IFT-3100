#include "PropertiesPanel.h"

#include "ImageImporter.h"
#include "imgui.h"

PropertiesPanel::PropertiesPanel() {
  auto floatDraw = [this](PropertyBase *prop) { drawFloatProperty(dynamic_cast<Property<float> *>(prop)); };
  auto imageImportDraw = [this](PropertyBase *prop) { drawImageImport(dynamic_cast<Property<ofImage> *>(prop)); };
  auto colorDraw = [this](PropertyBase *prop) { drawColorProperty(dynamic_cast<Property<ofColor> *>(prop)); };

  propertyDrawFunctions.emplace(PROPERTY_ID::SIZE, floatDraw);
  propertyDrawFunctions.emplace(PROPERTY_ID::RADIUS, floatDraw);
  propertyDrawFunctions.emplace(PROPERTY_ID::HEIGHT, floatDraw);

  propertyDrawFunctions.emplace(PROPERTY_ID::COLOR, colorDraw);
  propertyDrawFunctions.emplace(PROPERTY_ID::IMAGE_IMPORT, imageImportDraw);
}

void PropertiesPanel::drawFloatProperty(Property<float> *property) {
  auto temp = property->getValue();

  if (ImGui::SliderFloat(toString(property->getId()), &temp, 0.f, 500.f, "size")) {
    property->setValue(temp);
  }
}

void PropertiesPanel::drawColorProperty(Property<ofColor> *property) {
  auto temp = property->getValue();
  this->colorPicker.createColorPicker(temp);
  if (temp != property->getValue()) {
    property->setValue(temp);
  }
}

void PropertiesPanel::drawImageImport(Property<ofImage> *property) {
  if (ImGui::Button("Import image", ImVec2(100.f, 30.f))) {
    ImageImporter::importImage(property);
  }
  if (ImGui::Button("Remove image", ImVec2(100.f, 30.f))) {
    property->getValue().clear();
    property->setChanged(true);
  }
}

void PropertiesPanel::drawPanel(std::vector<SceneObject *> &objects) {
  if (objects.empty()) {
    return;
  }

  auto &properties = objects[0]->getProperties();

  for (auto &&property : properties) {
    this->propertyDrawFunctions.at(property.first)(property.second.get());
  }
}
