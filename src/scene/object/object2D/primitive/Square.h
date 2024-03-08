#pragma once
#include "object/object2D/Object2D.h"
#include "ofMain.h"
#include "raycasting/ray.h"

class Square : public Object2D {
public:
  Square(const glm::vec3 &centerPosition, const float halfWidth = 10.f, const float halfHeight = 10.f);
  Square(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition);
  static void drawPreview(const glm::vec3 &centerPosition, const float halfWidth = 10.f, const float halfHeight = 10.f);
  static void drawPreview(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition);

private:
  void initMesh(const glm::vec3 &centerPosition, const float halfWidth, const float halfHeight);
  void initContourMesh(const glm::vec3 &centerPosition, const float halfWidth, const float halfHeight);
  void initProperties(const float width, const float height);
  void setSize(const float width, const float height);
  void updateProperties() override;
};
