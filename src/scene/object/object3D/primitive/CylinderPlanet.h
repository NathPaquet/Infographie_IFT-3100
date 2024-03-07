#pragma once
#include "object/object3D/object3D.h"

class CylinderPlanet : public Object3D {
public:
  CylinderPlanet(const float x, const float y, const float z);

private:
  void setSize(const float radius, const float height);
  void updateProperties() override;
};
