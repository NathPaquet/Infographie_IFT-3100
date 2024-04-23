#pragma once
#include "sceneObject.h"

class Object3D : public SceneObject {
public:
  Object3D();
  void draw(bool isSelected, bool isBoundingBoxEnable, bool isObjectAxisEnable) const override;

private:
  void drawAxis() const override;
  void drawBoundingBox() const override;
  void drawAABB() const;

protected:
  void updateProperties() override;
};
