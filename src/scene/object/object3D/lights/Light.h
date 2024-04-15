#pragma once
#include "object/object3D/object3D.h"

class Light : public Object3D {
public:
  Light(const glm::vec3 &position);
  ~Light();

private:
  const float proportionToDraw = 3 / 16.f;
  const float initialPrimitiveRadius = 20 * proportionToDraw;

  void updateProperties() override;
  void updateLight();
  float getScale(float radius) const;

protected:
  ofLight light;
};
