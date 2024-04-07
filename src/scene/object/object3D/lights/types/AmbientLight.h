#pragma once
#include "ofColor.h"

class AmbientLight {
public:
  AmbientLight(const ofColor &color);
  void toggle();

private:
  ofColor color;
  bool isOn = true;

  void update();
};
