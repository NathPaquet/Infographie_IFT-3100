#pragma once

#include "imgui.h"

class ColorPicker {
public:
  ImVec4 getNormalizedColor() const;
  void createColorPicker();

private:
  ImVec4 normalizedColor;
  int rSlider;
  int gSlider;
  int bSlider;
  int hSlider;
  int sSlider;
  int BSlider;

  ImVec4 normalizedToRgb(const ImVec4 &normalized);
  ImVec4 rgbToNormalized(const ImVec4 &rgb);
  ImVec4 normalizedToHsb(const ImVec4 &normalized);
  ImVec4 hsbToNormalized(const ImVec4 &hsb);
};
