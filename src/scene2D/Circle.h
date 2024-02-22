#pragma once
#include "ofMain.h"
#include "raycasting/ray.h"
#include "sceneObject.h"

class Circle : public SceneObject {
public:
  Circle(const Ray &ray, const float &distance);
  static void drawDefaultPreview(const Ray &ray, const float &distance);

private:
  const int numberOfSection = 45;
  const float rotationPerVertex = 2 * glm::pi<float>() / numberOfSection;
  const glm::mat2x2 rotationMatrix = glm::mat2x2(
      std::cos(rotationPerVertex), -std::sin(rotationPerVertex),
      std::sin(rotationPerVertex), std::cos(rotationPerVertex));
};
