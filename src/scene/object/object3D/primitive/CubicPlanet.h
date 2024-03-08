#pragma once

#include "object/object3D/object3D.h"

class CubicPlanet : public Object3D {
public:
  CubicPlanet(const float x, const float y, const float z);

private:
  void set_size(const float size);
  void updateProperties() override;
};
