#pragma once

#include "Property.h"
#include "ofMain.h"

class Filtering {
public:
  static void applyBlur(ofTexture &texture);
  static void applySharpen(ofTexture &texture);
  static void applyGrey(ofTexture &texture);

private:
  static void applyConvolution(const ofPixels &inputPixels, ofPixels &outputPixels, const std::array<float, 9> &convolution);
  static void updateTexture(ofTexture &texture, const ofPixels &outputPixels);
  static void applyToAll(ofTexture &texture, std::function<void(const ofPixels &, ofPixels &)> callback);
  static ofPixels getPixels(const ofTexture &texture);
};
