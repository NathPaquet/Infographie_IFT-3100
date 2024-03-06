#pragma once
#include "object/sceneObject.h"
#include "ofMain.h"
#include "raycasting/ray.h"

class Circle : public SceneObject {
public:
  Circle(const glm::vec3 &centerPosition, const float radius = 20.f);
  Circle(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition);

  static void drawPreview(const glm::vec3 &centerPosition, const float radius = 20.f);
  static void drawPreview(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition);


private:
  void initMesh(const glm::vec3 &centerPosition, const float radius);
  const int numberOfSection = 45;
  const float rotationPerVertex = 2 * glm::pi<float>() / numberOfSection;
  const glm::mat2x2 rotationMatrix = glm::mat2x2(
      std::cos(rotationPerVertex), -std::sin(rotationPerVertex),
      std::sin(rotationPerVertex), std::cos(rotationPerVertex));
};
