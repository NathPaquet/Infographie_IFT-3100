#pragma once
#include "ofColor.h"

class AmbientLight {
public:
  AmbientLight();
  void toggle();
  bool isEnable() const;

private:
  ofColor color;
  bool isEnableStatus{true};

  void update();
};
