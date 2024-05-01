#pragma once
#include "ofTexture.h"

class TextureGenerator {
public:
  static ofPixels generateProceduralTexture(int width, int height, size_t seed = 42);
};
