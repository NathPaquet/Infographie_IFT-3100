#include "TextureEditor.h"

#include "Filtering.h"
#include "TextureGenerator.h"
#include "TextureRepository.h"
#include "constants.h"
#include "imgui.h"

TextureEditor::TextureEditor() {
  defaultMaterialShader = std::make_shared<ofShader>();
  defaultMaterialShader->load("shaders/texture");
}

void TextureEditor::displayEditorOptions() {
  ImGui::SetNextItemWidth(200.f);
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
      TextureRepository::configureTextureWithShader(result.fileName, this->defaultMaterialShader);
    }
  }
  if (ImGui::Button("Import single image")) {
    ofFileDialogResult result = ofSystemLoadDialog("Load image");
    if (result.bSuccess) {
      ofImage temp;
      temp.load(result.getPath());
      TextureRepository::addTextureFromSingleImage(temp, result.fileName);
      // TextureRepository::configureTextureWithShader(result.fileName, this->defaultMaterialShader);
    }
  }
}

void TextureEditor::displayTextureSpecificOptions(const TexturePack *texture) {
  ImGui::SetNextItemWidth(200.f);
  ImGui::SliderFloat("Perlin Noise Density", &displacementGenerationDensity, 0.0f, 0.025f);
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
  auto displacementMap = TextureGenerator::generateProceduralTexture(width, height, displacementGenerationDensity);
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
  }

  ImGui::TableNextColumn();
  ImGui::Text("Diffuse Map");
  if (texture->textureDiffuseMap.isAllocated()) {
    ImGui::Image(reinterpret_cast<void *>(static_cast<intptr_t>(texture->textureDiffuseMap.getTextureData().textureID)), textureSize);
  } else {
    ImGui::Text("No Diffuse Map");
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

std::shared_ptr<ofShader> TextureEditor::getDefaultShader() {
  return defaultMaterialShader;
}

void TextureEditor::drawMaterialProperties() {
  auto metallicity = currentTexture->getMetallicity();
  ImGui::SetNextItemWidth(200.f);
  if (ImGui::SliderFloat("Metallicity", &metallicity, Constants::MIN_METALLICITY_VALUE, Constants::MAX_METALLICITY_VALUE)) {
    TextureRepository::setMetallicity(currentTexture->packId, metallicity);
  }

  auto roughness = currentTexture->getRoughness();
  ImGui::SetNextItemWidth(200.f);
  if (ImGui::SliderFloat("Roughness", &roughness, Constants::MIN_ROUGHNESS_VALUE, Constants::MAX_ROUGHNESS_VALUE)) {
    TextureRepository::setRoughness(currentTexture->packId, roughness);
  }

  auto displacementStrenght = currentTexture->getDisplacementStrength();
  ImGui::SetNextItemWidth(200.f);
  if (ImGui::SliderFloat("Displacement Strength", &displacementStrenght, 0.f, 10.f)) {
    TextureRepository::setDisplacementStrength(currentTexture->packId, displacementStrenght);
  }

  auto brightness = currentTexture->getBrightness();
  ImGui::SetNextItemWidth(200.f);
  if (ImGui::SliderFloat("Brightness", &brightness, 0.f, 1.f)) {
    TextureRepository::setBrightness(currentTexture->packId, brightness);
    
  ImGui::SetNextItemWidth(200.f);
  if (ImGui::Checkbox(has_reinhard_tone_mapping ? "Reinhard Enable" : "ACES Filmic Enable", &has_reinhard_tone_mapping)) {
    TextureRepository::setReinhardToneMapping(currentTexture->packId, has_reinhard_tone_mapping);
  }
}
