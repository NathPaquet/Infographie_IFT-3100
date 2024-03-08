#pragma once
#include "sceneObject.h"

class Object3D : public SceneObject {
public:
  void draw(bool isSelected, bool isBoundingBoxEnable, bool isObjectAxisEnable) override;

private:
  void drawAxis() override;
  void drawBoundingBox() override;
  void drawAABB() const;
};
