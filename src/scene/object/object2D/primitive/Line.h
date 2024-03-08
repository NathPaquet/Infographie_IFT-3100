#pragma once
#include "object/object2D/Object2D.h"

class Line : public Object2D {
public:
  Line(const glm::vec3 &startPoint, const glm::vec3 &endPoint);
  static void drawPreview(const glm::vec3 &startPoint, const glm::vec3 &endPoint);

private:
  void initMesh(const glm::vec3 &startPoint, const glm::vec3 &endPoint);
  glm::vec3 startPoint;
  glm::vec3 endPoint;
};
