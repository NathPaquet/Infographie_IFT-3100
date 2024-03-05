#pragma once
#include "object/sceneObject.h"
#include "ofMain.h"
#include "raycasting/ray.h"
class Triangle : public SceneObject {
public:
  Triangle(const Ray &ray, const glm::vec3 &centerPosition);
  static void drawDefaultPreview(const glm::vec3 &centerPosition);
};
