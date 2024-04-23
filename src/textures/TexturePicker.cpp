#include "textures/TexturePicker.h"

#include "imgui.h"

#include <textures/TextureRepository.h>

const TexturePack *TexturePicker::drawTexturePicker(bool &changed, const TexturePack *currentTexture) {
  const TexturePack *result = nullptr;
  changed = false;

  if (ImGui::BeginCombo("Texture picker", currentTexture ? currentTexture->packId.data() : "Not selected")) {
    bool is_selected = !currentTexture;
    if (ImGui::Selectable("none", is_selected)) {
      result = nullptr;
      changed = true;
    }
    if (is_selected) {
      ImGui::SetItemDefaultFocus();
    }

    for (auto &&texture : TextureRepository::getTextures()) {
      is_selected = currentTexture ? texture->packId == currentTexture->packId : false;
      if (ImGui::Selectable(texture->packId.data(), is_selected)) {
        result = texture.get();
        changed = true;
      }
      if (is_selected) {
        ImGui::SetItemDefaultFocus();
      }
    }
    ImGui::EndCombo();
  }
  return result;
}
