#include "ColorPicker.h"

ImVec4 ColorPicker::getNormalizedColor() const {
  return normalizedColor;
}

bool ColorPicker::createColorPicker(ofColor &color) {
  bool changed = false;
  normalizedColor = color;
  ImGui::Text("Color picker:");

  if (ImGui::ColorPicker3("Color Picker", (float *)&normalizedColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel)) {
    color = normalizedColor;
    changed = true;
  }

  ImGui::Text("RGB slider:");
  bool rUsed = ImGui::SliderInt("R", &rSlider, 0, 255);
  bool gUsed = ImGui::SliderInt("G", &gSlider, 0, 255);
  bool bUsed = ImGui::SliderInt("B", &bSlider, 0, 255);

  if (rUsed || gUsed || bUsed) {
    normalizedColor = rgbToNormalized(ImVec4(rSlider, gSlider, bSlider, normalizedColor.w));
    color = normalizedColor;
    changed = true;
  } else {
    ImVec4 rgb = normalizedToRgb(normalizedColor);
    rSlider = rgb.x;
    gSlider = rgb.y;
    bSlider = rgb.z;
  }

  ImGui::Text("HSB slider:");
  bool hUsed = ImGui::SliderInt("H", &hSlider, 0, 360);
  bool sUsed = ImGui::SliderInt("S", &sSlider, 0, 100);
  bool BUsed = ImGui::SliderInt("Brightness", &BSlider, 0, 100);

  if (hUsed || sUsed || BUsed) {
    normalizedColor = hsbToNormalized(ImVec4(hSlider, sSlider, BSlider, normalizedColor.w));
    color = normalizedColor;
    changed = true;
  } else {
    ImVec4 hsb = normalizedToHsb(normalizedColor);
    hSlider = hsb.x;
    sSlider = hsb.y;
    BSlider = hsb.z;
  }
  return changed;
}

bool ColorPicker::createSimplifiedColorPicker(ofColor &color) {
  bool changed = false;
  normalizedColor = color;
  ImGui::Text("Color picker:");
  ImGui::SetNextItemWidth(200.f);
  if (ImGui::ColorPicker3("Color Picker", (float *)&normalizedColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel)) {
    color = normalizedColor;
    changed = true;
  }

  return changed;
}

ImVec4 ColorPicker::normalizedToRgb(const ImVec4 &normalized) {
  int r = std::round(normalized.x * 255);
  int g = std::round(normalized.y * 255);
  int b = std::round(normalized.z * 255);

  return ImVec4(r, g, b, normalized.w);
}

ImVec4 ColorPicker::rgbToNormalized(const ImVec4 &rgb) {
  int r = rgb.x;
  int g = rgb.y;
  int b = rgb.z;

  return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, rgb.w);
}

ImVec4 ColorPicker::normalizedToHsb(const ImVec4 &normalized) {
  float r = normalized.x;
  float g = normalized.y;
  float b = normalized.z;

  float v = std::max({r, g, b});
  float n = v - std::min({r, g, b});

  float h;
  if (n == 0) {
    h = 0;
  } else if (n != 0 && v == r) {
    h = (g - b) / n;
  } else if (v == g) {
    h = 2 + (b - r) / n;
  } else {
    h = 4 + (r - g) / n;
  }

  int hue = std::round(60 * (h < 0 ? h + 6 : h));
  int saturation = std::round(v == 0 ? 0 : (n / v) * 100);
  int brightness = std::round(v * 100);

  return ImVec4(hue, saturation, brightness, normalized.w);
}

static float f2(int n, float hue) {
  return fmod((n + hue / 60.0f), 6.0f);
}

static float f(int n, float hue, float saturation, float brightness) {
  float min = std::min({f2(n, hue), 4.0f - f2(n, hue), 1.0f});
  float max = std::max(0.0f, min);
  return brightness * (1.0f - saturation * max);
}

ImVec4 ColorPicker::hsbToNormalized(const ImVec4 &hsb) {
  float h = hsb.x;
  float s = hsb.y / 100.0f;
  float b = hsb.z / 100.0f;

  return ImVec4(f(5, h, s, b), f(3, h, s, b), f(1, h, s, b), hsb.w);
}
