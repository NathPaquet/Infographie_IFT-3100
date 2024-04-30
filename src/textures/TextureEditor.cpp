#include "TextureEditor.h"

#include "ImageImporter.h"
#include "TextureGenerator.h"
#include "Filtering.h"
#include "TextureRepository.h"
#include "imgui.h"

void TextureEditor::displayEditorOptions() {
  ImGui::BeginGroup();
  ImGui::Text("Texture Options");
  displayGenericOptions();
  ImGui::Separator();
  if (currentTexture) {
    displayTextureSpecificOptions(currentTexture);
  }
  ImGui::EndGroup();
}

void TextureEditor::displayGenericOptions() {
  if (ImGui::Button("Import texture pack folder")) {
    ofFileDialogResult result = ofSystemLoadDialog("Load Texture folder", true);
    if (result.bSuccess) {
      TextureRepository::addTexture(result.fileName);
    }
  }
  if (ImGui::Button("Import single image")) {
    ofFileDialogResult result = ofSystemLoadDialog("Load image");
    if (result.bSuccess) {
      ofImage temp;
      temp.load(result.getPath());
      TextureRepository::addTextureFromSingleImage(temp, result.fileName);
    }
  }
}

void TextureEditor::displayTextureSpecificOptions(const TexturePack *texture) {
  if (ImGui::Button("Generate a new displacement map")) {
    auto displacementMap = TextureGenerator::generateProceduralTexture(texture->textureDisplacementMap.getWidth(), texture->textureDisplacementMap.getHeight());
    // loading pixels in texture:
    ofTexture tex;
    tex.loadData((uint32_t *)displacementMap.getData(), displacementMap.getWidth(), displacementMap.getHeight(), displacementMap.getPixelFormat());
    TextureRepository::setDisplacementMap(texture->packId, tex);
  }
  if (ImGui::Button("Apply", ImVec2(100.f, 30.f))) {
    auto &id = currentTexture->packId;

    if (hasBlur) {
      TextureRepository::setTextureDiffuseMap(Filtering::applyBlur, id);
    }

    if (hasSharpen) {
      TextureRepository::setTextureDiffuseMap(Filtering::applySharpen, id);
    }

    if (hasGrey) {
      TextureRepository::setTextureDiffuseMap(Filtering::applyGrey, id);
  }
}

void TextureEditor::drawTextureEditor() {
  bool changed = false;
  auto &&pickerResult = texturePicker.drawTexturePicker(changed, currentTexture);
  if (changed) {
    setCurrentTexture(pickerResult);
  }

  displayEditorOptions();
  if (!currentTexture) {
    return;
  }
  ImGui::SameLine();
  drawImages(currentTexture);
}

void TextureEditor::setCurrentTexture(const TexturePack *texture) {
  currentTexture = texture;
}

void TextureEditor::drawImages(const TexturePack *texture) {
  const auto &totalSize = ImGui::GetContentRegionAvail();
  const auto textureSize = ImVec2(totalSize.x / 2, totalSize.y / 2 - 20.f);

  ImGui::BeginTable("TexturePackId", 2, ImGuiTableColumnFlags_WidthStretch, totalSize);
  ImGui::TableNextColumn();
  ImGui::Text("Displacement Map");
  if (texture->textureDisplacementMap.isAllocated()) {
    ImGui::Image(reinterpret_cast<void *>(static_cast<intptr_t>(texture->textureDisplacementMap.getTextureData().textureID)), textureSize);
  } else {
    ImGui::Text("No Displacement Map");
    ImGui::Button("Generate a procedural texture");
  }

  ImGui::TableNextColumn();
  ImGui::Text("Diffuse Map");
  if (texture->textureDiffuseMap.isAllocated()) {
    ImGui::Image(reinterpret_cast<void *>(static_cast<intptr_t>(texture->textureDiffuseMap.getTextureData().textureID)), textureSize);
  } else {
    ImGui::Text("No Diffuse Map");
    ImGui::Button("DO SOMETHING");
  }

  ImGui::TableNextColumn();
  ImGui::Text("Normal Map");
  if (texture->textureNormalMap.isAllocated()) {
    ImGui::Image(reinterpret_cast<void *>(static_cast<intptr_t>(texture->textureNormalMap.getTextureData().textureID)), textureSize);
  } else {
    ImGui::Text("No Normal map");
  }

  ImGui::TableNextColumn();
  ImGui::Text("AO Rough Metal");
  if (texture->textureAORoughMetal.isAllocated()) {
    ImGui::Image(reinterpret_cast<void *>(static_cast<intptr_t>(texture->textureAORoughMetal.getTextureData().textureID)), textureSize);
  } else {
    ImGui::Text("No Roughness map");
  }

  ImGui::EndTable();
}
