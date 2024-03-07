#pragma once

#include "object/sceneObject.h"

class Camera : public SceneObject {
public:
  Camera(ofVec3f position);
  ofCamera *getCamera();

private:
  const float CAMERA_RADIUS = 2.f;
  const float CAMERA_LINE_LENGTH = CAMERA_RADIUS * 2.5f;
  std::unique_ptr<ofCamera> camera;

  void updateProperties();
};
