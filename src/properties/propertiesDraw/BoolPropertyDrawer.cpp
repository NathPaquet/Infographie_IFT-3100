#include "BoolPropertyDrawer.h"

#include <imgui.h>

void BoolPropertyDrawer::draw(std::vector<PropertyBase *> &objectsProperty) {
  auto &&firstObjectProperty = dynamic_cast<Property<bool> *>(objectsProperty[0]);
  auto &&propertyValue = firstObjectProperty->getValue();

  bool temp = propertyValue;
  if (ImGui::Checkbox(toString(firstObjectProperty->getId()), &temp)) {
    for (auto &&objectProperty : objectsProperty) {
      auto property = dynamic_cast<Property<bool> *>(objectProperty);
      property->setValue(temp);
    }
  }
}
