#pragma once

#include "Property.h"
#include "ofMain.h"

class Filtering {
public:
  void applyBlur(const std::vector<PropertyBase *> &objectsProperty);
  void applySharpen(const std::vector<PropertyBase *> &objectsProperty);
  void applyGrey(const std::vector<PropertyBase *> &objectsProperty);

private:
  void applyConvolution(const ofImage &inputImage, ofImage &outputImage, const std::array<float, 9> &convolution);
  void updateInputImage(ofImage &inputImage, const ofImage &outputImage);
  void applyToAll(const std::vector<PropertyBase *> &objectsProperty, std::function<void(ofImage &, ofImage &)> callback);
};
