#pragma once

#include "sceneObject.h"

class CubicPlanet : public SceneObject {
public:
  CubicPlanet(const float x, const float y, const float z);

private:
  void set_size(const float size);
  void updateProperties() override;
};
