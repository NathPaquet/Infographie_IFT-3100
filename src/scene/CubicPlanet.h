#pragma once

#include "sceneObject.h"

class CubicPlanet : public SceneObject {
public:
  void draw_properties() override;
  CubicPlanet(const float x, const float y, const float z);

private:
  float size = 20.f;
  void set_size(const float size);
};
