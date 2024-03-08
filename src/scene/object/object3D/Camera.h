#pragma once

#include "object3D.h"

class Camera : public Object3D {
public:
  Camera(const glm::vec3 &position);
  ofCamera *getCamera();

private:
  const float CAMERA_RADIUS = 2.f;
  const float CAMERA_LINE_LENGTH = CAMERA_RADIUS * 2.5f;
  std::unique_ptr<ofCamera> camera;

  void updateProperties() override;
};
