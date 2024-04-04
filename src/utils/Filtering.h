#pragma once

#include "Property.h"
#include "ofMain.h"

class Filtering {
public:
  void applyBlur(const std::vector<PropertyBase *> &objectsProperty);
  void applySharpen(const std::vector<PropertyBase *> &objectsProperty);
  void applyGrey(const std::vector<PropertyBase *> &objectsProperty);

private:
  const float c = 1 / 9.f;
  const std::array<float, 9> convolution_blur =
      {
          c,
          c,
          c,
          c,
          c,
          c,
          c,
          c,
          c,
  };
  const std::array<float, 9> convolution_sharpen =
      {
          0.f,
          -1.f,
          0.f,
          -1.f,
          5.f,
          -1.f,
          0.f,
          -1.f,
          0.f,
  };

  void applyConvolution(ofImage &inputImage, const std::array<float, 9> &convolution);
  void updateInputImage(ofImage &inputImage, const ofImage &outputImage);
  void applyToAll(const std::vector<PropertyBase *> &objectsProperty, std::function<void(ofImage &)> callback);
};
