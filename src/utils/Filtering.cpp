#include "Filtering.h"

void Filtering::applyBlur(const std::vector<PropertyBase *> &objectsProperty) {
  applyToAll(objectsProperty, [&](ofImage &inputImage) {
    applyConvolution(inputImage, convolution_blur);
  });
}

void Filtering::applySharpen(const std::vector<PropertyBase *> &objectsProperty) {
  applyToAll(objectsProperty, [&](ofImage &inputImage) {
    applyConvolution(inputImage, convolution_sharpen);
  });
}

void Filtering::applyGrey(const std::vector<PropertyBase *> &objectsProperty) {
  applyToAll(objectsProperty, [&](ofImage &inputImage) {
    auto outputImage = inputImage;

    for (int y = 0; y < inputImage.getHeight(); y++) {
      for (int x = 0; x < inputImage.getWidth(); x++) {
        const auto &color = inputImage.getColor(x, y);
        float grey = (color.r + color.g + color.b) / 3.f;

        ofColor newColor = ofColor(grey);
        outputImage.setColor(x, y, newColor);
      }
    }

    updateInputImage(inputImage, outputImage);
  });
}

void Filtering::applyConvolution(ofImage &inputImage, const std::array<float, 9> &convolution) {
  auto outputImage = inputImage;

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

  updateInputImage(inputImage, outputImage);
}

void Filtering::updateInputImage(ofImage &inputImage, const ofImage &outputImage) {
  inputImage.setFromPixels(outputImage.getPixels());
  inputImage.update();
}

void Filtering::applyToAll(const std::vector<PropertyBase *> &objectsProperty, std::function<void(ofImage &)> callback) {
  for (auto &&objectProperty : objectsProperty) {
    auto property = dynamic_cast<Property<ofImage> *>(objectProperty);
    ofImage &inputImage = property->getValue();

    callback(inputImage);

    property->setChanged(true);
  }
}
