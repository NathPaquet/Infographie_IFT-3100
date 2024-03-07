#pragma once
#include "object/object2D/Object2D.h"
#include "ofMain.h"
#include "raycasting/ray.h"

class Triangle : public Object2D {
public:
  Triangle(const glm::vec3 &centerPosition, const glm::vec2 &firstPoint = {20, 20});
  Triangle(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition);

  static void drawPreview(const glm::vec3 &centerPosition, const glm::vec2 &firstPoint = {20, 20});
  static void drawPreview(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition);

private:
  glm::vec2 firstPointDirection;
  void initMesh(const glm::vec3 &centerPosition, const glm::vec2 &direction, const float radius);
  void initProperties(const float radius);
  void setSize(const float radius);
  void updateProperties() override;
};
