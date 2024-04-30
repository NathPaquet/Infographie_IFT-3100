#include "TextureEditor.h"

#include "imgui.h"

void TextureEditor::drawTextureEditor() {
  bool changed = false;
  auto &&pickerResult = texturePicker.drawTexturePicker(changed, currentTexture);
  if (changed) {
    setCurrentTexture(pickerResult);
  }

  if (!currentTexture) {
    return;
  }

  displayImage(currentTexture);
}

void TextureEditor::setCurrentTexture(const TexturePack *texture) {
  currentTexture = texture;
}

void TextureEditor::displayImage(const TexturePack *texture) {
  ImGui::Image(reinterpret_cast<void *>(static_cast<intptr_t>(texture->textureDisplacementMap.getTextureData().textureID)), ImVec2(1024, 1024));
}
