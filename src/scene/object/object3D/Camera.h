#pragma once

#include "object/sceneObject.h"

class Camera : public SceneObject {
public:
  Camera(ofVec3f position);
  ofEasyCam *getCamera();

private:
  const float CAMERA_RADIUS = 2.f;
  const float CAMERA_LINE_LENGTH = 5.f;
  std::unique_ptr<ofEasyCam> camera;

  void updateProperties();
};
