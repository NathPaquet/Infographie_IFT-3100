#pragma once
#include "object/sceneObject.h"
#include "ofMain.h"
#include "raycasting/ray.h"
class Square : public SceneObject {
public:
  Square(const glm::vec3 &centerPosition);
  static void drawDefaultPreview(const glm::vec3 &centerPosition);
};
