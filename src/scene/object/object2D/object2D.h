#pragma once
#include "sceneObject.h"

class Object2D : public SceneObject {
public:
  Object2D();
  void draw(bool isSelected, bool isBoundingBoxEnable, bool isObjectAxisEnable) const override;

private:
  void drawAxis() const override;
  void drawBoundingBox() const override;
  void drawAABB() const;

protected:
  void updateProperties() override;
};
