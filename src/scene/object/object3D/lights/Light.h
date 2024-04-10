#pragma once
#include "object/object3D/object3D.h"

class Light : public Object3D {
public:
  Light(const glm::vec3 &position);

private:
  const float propotionToDraw = 1 / 4.f;
  const float initialPrimitiveRadius = 20 * propotionToDraw;

  void updateProperties() override;
  void updateLight();
  float getScale(float radius) const;

protected:
  ofLight light;
};
