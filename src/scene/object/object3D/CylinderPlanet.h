#pragma once
#include "object/sceneObject.h"

class CylinderPlanet : public SceneObject {
public:
  CylinderPlanet(const float x, const float y, const float z);

private:
  const float DEFAULT_HEIGHT = 20.f;
  const float DEFAULT_RADIUS = 20.f;

  void setSize(const float radius, const float height);
  void updateProperties() override;
};
