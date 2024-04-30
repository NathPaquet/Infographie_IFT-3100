#include "TextureEditor.h"

#include "imgui.h"

void TextureEditor::displayEditorOptions() {
  ImGui::BeginGroup();
  ImGui::SeparatorText("Texture Editor Options");
  ImGui::Checkbox("Blur", &hasBlur);
  ImGui::Checkbox("Sharpen", &hasSharpen);
  ImGui::Checkbox("Grey", &hasGrey);

  if (ImGui::Button("Apply", ImVec2(100.f, 30.f))) {
    if (hasBlur) {
      filtering.applyBlur(currentTexture);
    }

    if (hasSharpen) {
      filtering.applySharpen(currentTexture);
    }

    if (hasGrey) {
      filtering.applyGrey(currentTexture);
    }
  }

  ImGui::EndGroup();
}

void TextureEditor::drawTextureEditor() {
  bool changed = false;
  auto &&pickerResult = texturePicker.drawTexturePicker(changed, currentTexture);
  if (changed) {
    setCurrentTexture(pickerResult);
  }

  if (!currentTexture) {
    return;
  }
  displayEditorOptions();
  ImGui::SameLine();
  displayImage(currentTexture);
}

void TextureEditor::setCurrentTexture(const TexturePack *texture) {
  currentTexture = texture;
}

void TextureEditor::displayImage(const TexturePack *texture) {
  ImGui::Image(reinterpret_cast<void *>(static_cast<intptr_t>(texture->textureDisplacementMap.getTextureData().textureID)), ImVec2(1024, 1024));
}
