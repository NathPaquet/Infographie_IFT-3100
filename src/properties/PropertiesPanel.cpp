#include "PropertiesPanel.h"

#include "imgui.h"

void PropertiesPanel::drawFloat(Property<float> *property) {
  auto temp = property->getValue();

  if (ImGui::SliderFloat("Radius", &temp, 0.f, 500.f, "size")) {
    property->setValue(temp);
  }
}

void PropertiesPanel::drawPanel(std::vector<SceneObject *> &objects) {
  if (objects.empty()) {
    return;
  }

  auto &properties = objects[0]->getProperties();

  for (auto &&property : properties) {
    if (property.first == "Size") {
      drawFloat(dynamic_cast<Property<float> *>(property.second.get()));
    }
  }
}
