#include "BoolPropertyDrawer.h"

#include <imgui.h>

void BoolPropertyDrawer::draw(std::vector<PropertyBase *> &objectsProperty) {
  auto &&firstObjectProperty = dynamic_cast<Property<bool> *>(objectsProperty[0]);
  auto &&propertyValue = firstObjectProperty->getValue();

  ImGui::SeparatorText(toString(firstObjectProperty->getId()));
  bool temp = propertyValue;
  if (ImGui::Checkbox("Draw Wireframe Only", &temp)) {
    for (auto &&objectProperty : objectsProperty) {
      auto property = dynamic_cast<Property<bool> *>(objectProperty);
      property->setValue(temp);
    }
  }
}
