#pragma once
#include "sceneObject.h"

class Object2D : public SceneObject {
public:
  void draw(bool isSelected, bool isBoundingBoxEnable, bool isObjectAxisEnable) override;

private:
  void drawAxis() override;
  void drawBoundingBox() override;
};
