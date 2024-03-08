#pragma once
#include "sceneObject.h"

class Object2D : public SceneObject {
public:
  Object2D();
  void draw(bool isSelected, bool isBoundingBoxEnable, bool isObjectAxisEnable) override;

private:
  void drawAxis() override;
  void drawBoundingBox() override;
  void drawAABB() const;

protected:
  void updateProperties() override;
};
