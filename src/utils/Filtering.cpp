#include "Filtering.h"

#include <constants.h>

void Filtering::applyBlur(ofTexture &texture) {
  applyToAll(texture, [&](const ofPixels &inputPixels, ofPixels &outputPixels) {
    applyConvolution(inputPixels, outputPixels, Constants::CONVOLUTION_BLUR);
  });
}

void Filtering::applySharpen(ofTexture &texture) {
  applyToAll(texture, [&](const ofPixels &inputPixels, ofPixels &outputPixels) {
    applyConvolution(inputPixels, outputPixels, Constants::CONVOLUTION_SHARPEN);
  });
}

void Filtering::applyGrey(ofTexture &texture) {
  applyToAll(texture, [&](const ofPixels &inputPixels, ofPixels &outputPixels) {
    for (int y = 0; y < inputPixels.getHeight(); y++) {
      for (int x = 0; x < inputPixels.getWidth(); x++) {
        const auto &color = inputPixels.getColor(x, y);
        float grey = (color.r + color.g + color.b) / 3.f;

        ofColor newColor = ofColor(grey);
        outputPixels.setColor(x, y, newColor);
      }
    }
  });
}

void Filtering::applyConvolution(const ofPixels &inputPixels, ofPixels &outputPixels, const std::array<float, 9> &convolution) {
  for (int y = 1; y < inputPixels.getHeight() - 1; y++) {
    for (int x = 1; x < inputPixels.getWidth() - 1; x++) {
      float sumR = 0, sumG = 0, sumB = 0;

      for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
          ofColor color = inputPixels.getColor(x + i, y + j);
          int index = (i + 1) * 3 + (j + 1);

          sumR += color.r * convolution.at(index);
          sumG += color.g * convolution.at(index);
          sumB += color.b * convolution.at(index);
        }
      }

      sumR = ofClamp(sumR, 0, 255);
      sumG = ofClamp(sumG, 0, 255);
      sumB = ofClamp(sumB, 0, 255);

      outputPixels.setColor(x, y, ofColor(sumR, sumG, sumB));
    }
  }
}

void Filtering::updateTexture(ofTexture &texture, const ofPixels &outputPixels) {
  // 1
  texture.loadData(outputPixels);

  // 2
  /*texture.bind();
  glTexSubImage2D(texture.texData.textureTarget, 0, 0, 0, outputPixels.getWidth(), outputPixels.getHeight(), ofGetGlInternalFormat(outputPixels), GL_UNSIGNED_BYTE, outputPixels.getData());
  texture.unbind();*/
}

void Filtering::applyToAll(ofTexture &texture, std::function<void(const ofPixels &, ofPixels &)> callback) {
  auto &inputPixels = getPixels(texture);
  auto outputPixels = inputPixels;

  callback(inputPixels, outputPixels);

  updateTexture(texture, outputPixels);
}

ofPixels Filtering::getPixels(const ofTexture &texture) {
  ofPixels pixels;
  texture.readToPixels(pixels);

  return pixels;
}
