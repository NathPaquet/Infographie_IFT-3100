#pragma once
#include "object/sceneObject.h"


class Line : public SceneObject {
public:
  Line(const glm::vec3 &startPoint, const glm::vec3 &endPoint);
  static void drawPreview(const glm::vec3 &startPoint, const glm::vec3 &endPoint);


private:
  void initMesh(const glm::vec3 &startPoint, const glm::vec3 &endPoint);
  glm::vec3 startPoint;
  glm::vec3 endPoint;
};
