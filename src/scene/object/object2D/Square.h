#pragma once
#include "object/sceneObject.h"
#include "ofMain.h"
#include "raycasting/ray.h"
class Square : public SceneObject {
public:
  Square(const glm::vec3 &centerPosition, const float halfSize=10.f);
  Square(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition);
  static void drawPreview(const glm::vec3 &centerPosition, const float halfSize = 10.f);
  static void drawPreview(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition);

private:
  void initMesh(const glm::vec3 &centerPosition, const float halfSize);
};
