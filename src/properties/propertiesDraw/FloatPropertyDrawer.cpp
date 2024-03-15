#include "FloatPropertyDrawer.h"

#include <imgui.h>

void FloatPropertyDrawer::draw(std::vector<PropertyBase *> &objectsProperty) {
  auto firstObjectProperty = dynamic_cast<Property<float> *>(objectsProperty[0]);
  auto propertyValue = firstObjectProperty->getValue();

  ImGui::SeparatorText(toString(firstObjectProperty->getId()));

  if (ImGui::SliderFloat(toString(firstObjectProperty->getId()), &propertyValue, this->min, this->max, NULL, ImGuiSliderFlags_AlwaysClamp)) { // Returns true if the value was changed
    for (auto &&objectProperty : objectsProperty) {
      auto property = dynamic_cast<Property<float> *>(objectProperty);
      property->setValue(propertyValue);
    }
  }

  if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary)) {
    ImGui::SetItemTooltip("CTRL+Click to input value.");
  }
}

FloatPropertyDrawer::FloatPropertyDrawer(const float min, const float max):
    min(min), max(max) {
}
