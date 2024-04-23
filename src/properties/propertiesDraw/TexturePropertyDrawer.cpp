#include "TexturePropertyDrawer.h"

#include <imgui.h>

void TexturePropertyDrawer::draw(std::vector<PropertyBase *> &objectsProperty) {
  auto firstObjectProperty = dynamic_cast<Property<const TexturePack *> *>(objectsProperty[0]);
  auto propertyValue = firstObjectProperty->getValue();

  ImGui::SeparatorText(toString(firstObjectProperty->getId()));
  bool isChanged = false;

  const TexturePack *pickerResult = this->texturePicker.drawTexturePicker(isChanged, propertyValue);

  if (isChanged) {
    for (auto &&objectProperty : objectsProperty) {
      auto property = dynamic_cast<Property<const TexturePack *> *>(objectProperty);
      property->setValue(pickerResult);
    }
  }
}
