#pragma once
#include "object/object2D/Object2D.h"
#include "ofMain.h"
#include "raycasting/ray.h"

class Square : public Object2D {
public:
  Square(const glm::vec3 &centerPosition, const float halfSize = 10.f);
  Square(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition);
  static void drawPreview(const glm::vec3 &centerPosition, const float halfSize = 10.f);
  static void drawPreview(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition);

private:
  void initMesh(const glm::vec3 &centerPosition, const float halfSize);
  void initContourMesh(const glm::vec3 &centerPosition, const float halfSize);
  void initProperties(const float halfSize);
  void setSize(const float halfSize);
  void updateProperties() override;
};
