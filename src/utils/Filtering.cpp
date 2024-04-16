#include "Filtering.h"

#include <constants.h>

void Filtering::applyBlur(const std::vector<PropertyBase *> &objectsProperty) {
  applyToAll(objectsProperty, [&](ofImage &inputImage, ofImage &outputImage) {
    applyConvolution(inputImage, outputImage, Constants::CONVOLUTION_BLUR);
  });
}

void Filtering::applySharpen(const std::vector<PropertyBase *> &objectsProperty) {
  applyToAll(objectsProperty, [&](ofImage &inputImage, ofImage &outputImage) {
    applyConvolution(inputImage, outputImage, Constants::CONVOLUTION_SHARPEN);
  });
}

void Filtering::applyGrey(const std::vector<PropertyBase *> &objectsProperty) {
  applyToAll(objectsProperty, [&](ofImage &inputImage, ofImage &outputImage) {
    for (int y = 0; y < inputImage.getHeight(); y++) {
      for (int x = 0; x < inputImage.getWidth(); x++) {
        const auto &color = inputImage.getColor(x, y);
        float grey = (color.r + color.g + color.b) / 3.f;

        ofColor newColor = ofColor(grey);
        outputImage.setColor(x, y, newColor);
      }
    }
  });
}

void Filtering::applyConvolution(const ofImage &inputImage, ofImage &outputImage, const std::array<float, 9> &convolution) {
  for (int y = 1; y < inputImage.getHeight() - 1; y++) {
    for (int x = 1; x < inputImage.getWidth() - 1; x++) {
      float sumR = 0, sumG = 0, sumB = 0;

      for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
          ofColor color = inputImage.getColor(x + i, y + j);
          int index = (i + 1) * 3 + (j + 1);

          sumR += color.r * convolution.at(index);
          sumG += color.g * convolution.at(index);
          sumB += color.b * convolution.at(index);
        }
      }

      sumR = ofClamp(sumR, 0, 255);
      sumG = ofClamp(sumG, 0, 255);
      sumB = ofClamp(sumB, 0, 255);
      outputImage.setColor(x, y, ofColor(sumR, sumG, sumB));
    }
  }
}

void Filtering::updateInputImage(ofImage &inputImage, const ofImage &outputImage) {
  inputImage.setFromPixels(outputImage.getPixels());
  inputImage.update();
}

void Filtering::applyToAll(const std::vector<PropertyBase *> &objectsProperty, std::function<void(ofImage &, ofImage &)> callback) {
  for (auto &&objectProperty : objectsProperty) {
    auto property = dynamic_cast<Property<ofImage> *>(objectProperty);
    ofImage &inputImage = property->getValue();
    auto outputImage = inputImage;

    callback(inputImage, outputImage);

    updateInputImage(inputImage, outputImage);
    property->setChanged(true);
  }
}
