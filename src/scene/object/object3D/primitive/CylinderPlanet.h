#pragma once
#include "object/sceneObject.h"

class CylinderPlanet : public SceneObject {
public:
  CylinderPlanet(const float x, const float y, const float z);

private:
  void setSize(const float radius, const float height);
  void updateProperties() override;
};
