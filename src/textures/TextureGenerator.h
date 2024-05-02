#pragma once
#include "ofTexture.h"

class TextureGenerator {
public:
  static ofPixels generateProceduralTexture(int width, int height, float density);
};
