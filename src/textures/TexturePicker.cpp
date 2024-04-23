#include "textures/TexturePicker.h"

#include "imgui.h"

#include <textures/TextureRepository.h>

const TexturePack *TexturePicker::drawTexturePicker(const TexturePack *currentTexture) {
  auto temp = &currentTexture;
  const TexturePack *result = nullptr;
  if (ImGui::BeginCombo("ColorPicker", currentTexture->packId.data())) {
    for (auto &&texture : TextureRepository::getTextures()) {
      const bool is_selected = texture->packId == currentTexture->packId;
      if (ImGui::Selectable(texture->packId.data(), is_selected)) {
        result = texture.get();
      }

      if (is_selected) {
        ImGui::SetItemDefaultFocus();
      }
    }
    ImGui::EndCombo();
  }
  return result;
}
