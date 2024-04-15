#include "ImagePropertyDrawer.h"

#include <ImageImporter.h>
#include <imgui.h>
#include <ofImage.h>

void ImagePropertyDrawer::draw(std::vector<PropertyBase *> &objectsProperty) {
  auto firstObjectProperty = dynamic_cast<Property<ofImage> *>(objectsProperty[0]);
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
