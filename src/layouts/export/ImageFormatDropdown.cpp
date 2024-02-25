#include "ImageFormatDropdown.h"

#include "ImGui.h"

void ImageFormatDropdown::create() {
  if (ImGui::BeginCombo("Image Format", selectedFormat.c_str())) {
    for (const auto &format : formats) {
      if (ImGui::Selectable(format.c_str())) {
        selectedFormat = format;
      }
    }

    ImGui::EndCombo();
  }
}

std::string ImageFormatDropdown::getSelectedFormat() const {
  return selectedFormat;
}
