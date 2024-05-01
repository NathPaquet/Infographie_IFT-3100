#include "TextureEditor.h"

#include "Filtering.h"
#include "ImageImporter.h"
#include "TextureGenerator.h"
#include "TextureRepository.h"
#include "constants.h"
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
    generateDisplacementMapForTexture(texture);
  }
  ImGui::Checkbox("Blur", &this->hasBlur);
  ImGui::Checkbox("Sharpen", &this->hasSharpen);
  ImGui::Checkbox("Grey", &this->hasGrey);

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

  drawMaterialProperties();
}

void TextureEditor::generateDisplacementMapForTexture(const TexturePack *texture) {
  float width;
  float height;
  if (!texture->textureDisplacementMap.isAllocated()) {
    width = 1024;
    height = 1024;
  } else {
    width = texture->textureDisplacementMap.getWidth();
    height = texture->textureDisplacementMap.getHeight();
  }
  auto displacementMap = TextureGenerator::generateProceduralTexture(width, height);
  // loading pixels in texture:
  ofTexture tex;
  tex.loadData(displacementMap.getData(), displacementMap.getWidth(), displacementMap.getHeight(), GL_RGBA);
  TextureRepository::setDisplacementMap(texture->packId, tex);
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
    if (ImGui::Button("Generate a new displacement map")) {
      generateDisplacementMapForTexture(texture);
    }
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

void TextureEditor::drawMaterialProperties() {
  auto metallicity = currentTexture->getMetallicity();
  if (ImGui::SliderFloat("Metallicity", &metallicity, Constants::MIN_METALLICITY_VALUE, Constants::MAX_METALLICITY_VALUE)) {
    auto &id = currentTexture->packId;
    TextureRepository::setMetallicity(id, metallicity);
  }

  auto roughness = currentTexture->getRoughness();
  if (ImGui::SliderFloat("Roughness", &roughness, Constants::MIN_ROUGHNESS_VALUE, Constants::MAX_ROUGHNESS_VALUE)) {
    auto &id = currentTexture->packId;
    TextureRepository::setRoughness(id, roughness);
  }
}
