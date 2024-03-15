#include "ColorPropertyDrawer.h"

#include <imgui.h>
#include <ofColor.h>

void ColorPropertyDrawer::draw(std::vector<PropertyBase *> &objectsProperty) {
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
