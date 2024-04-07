#pragma once
#include "object/object3D/object3D.h"

class Light : public Object3D {
public:
  Light(const glm::vec3 &position);

private:
  void updateProperties() override;
  void updateLight();

protected:
  ofLight light;
};
