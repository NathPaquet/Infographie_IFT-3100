#include "TextureGenerator.h"

#include "ofImage.h"
#include "ofMath.h"
#include "ofPixels.h"

#include <random>

ofPixels TextureGenerator::generateProceduralTexture(int width, int height, float density) {
  ofPixels displacementMap;
  auto randomValue = ofRandom(0.01f);
  displacementMap.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      float noiseValue = ofNoise(x * (density + randomValue), y * (density + randomValue));

      float pixelValue = ofMap(noiseValue, 0, 1, 0, 1);

      // displacementMap.setColor(x, y, ofColor(pixelValue));
      displacementMap.setColor(x, y, ofColor(pixelValue * 255, pixelValue * 255, pixelValue * 255, 255));
    }
  }
  // ofImage temp = ofImage(displacementMap);
  // temp.save("test.png");

  return displacementMap;
}
