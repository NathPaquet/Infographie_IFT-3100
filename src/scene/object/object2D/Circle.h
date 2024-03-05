#pragma once
#include "object/sceneObject.h"
#include "ofMain.h"
#include "raycasting/ray.h"

class Circle : public SceneObject {
public:
  Circle(const glm::vec3 &centerPosition);
  static void drawDefaultPreview(const glm::vec3 &centerPosition);

private:
  const int numberOfSection = 45;
  const float rotationPerVertex = 2 * glm::pi<float>() / numberOfSection;
  const glm::mat2x2 rotationMatrix = glm::mat2x2(
      std::cos(rotationPerVertex), -std::sin(rotationPerVertex),
      std::sin(rotationPerVertex), std::cos(rotationPerVertex));
};
