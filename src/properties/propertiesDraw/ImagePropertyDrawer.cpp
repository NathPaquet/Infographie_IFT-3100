#include "ImagePropertyDrawer.h"

#include <ImageImporter.h>
#include <imgui.h>
#include <ofImage.h>

void ImagePropertyDrawer::draw(std::vector<PropertyBase *> &objectsProperty) {
  drawImport(objectsProperty);
  drawFiltering(objectsProperty);
}

void ImagePropertyDrawer::drawImport(const std::vector<PropertyBase *> &objectsProperty) {
  auto firstObjectProperty = dynamic_cast<Property<ofImage> *>(objectsProperty.front());
  ImGui::SeparatorText(toString(firstObjectProperty->getId()));

  if (ImGui::Button("Import image", ImVec2(100.f, 30.f))) {
    ImageImporter::importImage(objectsProperty);
  }
  /*if (ImGui::Button("Remove image", ImVec2(100.f, 30.f))) {
    for (auto &&objectProperty : objectsProperty) {
      auto property = dynamic_cast<Property<ofImage> *>(objectProperty);
      property->getValue().clear();
      property->setChanged(true);
    }
  }*/
}

void ImagePropertyDrawer::drawFiltering(const std::vector<PropertyBase *> &objectsProperty) {
  ImGui::SeparatorText("Filtering");

  ImGui::Checkbox("Blur", &hasBlur);
  ImGui::Checkbox("Sharpen", &hasSharpen);
  ImGui::Checkbox("Grey", &hasGrey);

  if (ImGui::Button("Apply", ImVec2(100.f, 30.f))) {
    if (hasBlur) {
      filtering.applyBlur(objectsProperty);
      ofLogNotice("ImagePropertyDrawer") << "Apply Blur!";
    }

    if (hasSharpen) {
      filtering.applySharpen(objectsProperty);
      ofLogNotice("ImagePropertyDrawer") << "Apply Sharpen!";
    }

    if (hasGrey) {
      filtering.applyGrey(objectsProperty);
      ofLogNotice("ImagePropertyDrawer") << "Apply Grey!";
    }
  }
}
