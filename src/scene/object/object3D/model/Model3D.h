#pragma once
#include "object/object3D/object3D.h"

#include <ray.h>

class Model3D : public Object3D {
public:
  Model3D(const glm::vec3 &position, const string &modelPath);

private:
  float initialScaleFactor;
  void set_size(const float size);
  ofVec3f getBoundingBoxDimensions(const ofMesh &mesh) const;
  void drawAxis() const override;
  void updateProperties() override;
};
