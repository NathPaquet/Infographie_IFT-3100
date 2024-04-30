#include "TextureGenerator.h"

#include "ofImage.h"
#include "ofMath.h"
#include "ofPixels.h"

ofPixels TextureGenerator::generateProceduralTexture(int width, int height, size_t seed) {
  ofPixels displacementMap;
  ofSetRandomSeed(seed);
  displacementMap.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      float noiseValue = ofNoise(x * 0.01, y * 0.01);

      float pixelValue = ofMap(noiseValue, 0, 1, 0, 1);

      // displacementMap.setColor(x, y, ofColor(pixelValue));
      displacementMap.setColor(x, y, ofColor(pixelValue * 255, pixelValue * 150, pixelValue * 255, 255));
    }
  }
  // ofImage temp = ofImage(displacementMap);
  // temp.save("test.png");

  return displacementMap;
}
