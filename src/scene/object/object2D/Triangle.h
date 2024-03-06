#pragma once
#include "object/sceneObject.h"
#include "ofMain.h"
#include "raycasting/ray.h"
class Triangle : public SceneObject {
public:
  Triangle(const glm::vec3 &centerPosition, const glm::vec2 &firstPoint = {20, 20});
  Triangle(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition);

  static void drawPreview(const glm::vec3 &centerPosition, const glm::vec2 &firstPoint = {20,20});
  static void drawPreview(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition);

private:
  void initMesh(const glm::vec3 &centerPosition, const glm::vec2 &firstPoint);
};
