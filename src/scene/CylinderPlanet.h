#pragma once
#include "sceneObject.h"

class CylinderPlanet : public SceneObject {
public:
  void draw_properties() override;
  CylinderPlanet(const float x, const float y, const float z);

private:
  void setRadius(const float radius);
  void setHeight(const float height);
  float radius = 20.f;
  float height = 20.f;
};
