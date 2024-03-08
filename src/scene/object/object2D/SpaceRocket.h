#pragma once
#include "Square.h"
#include "Triangle.h"
#include "sceneObject.h"

class SpaceRocket : public SceneObject {
public:
  SpaceRocket(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition);
  SpaceRocket(const glm::vec3 &centerPosition, const float width = 20.f, const float height = 40.f);

  static void drawPreview(const glm::vec3 &centerPosition, const float width = 20.f, const float height = 40.f);
  static void drawPreview(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition);

private:
  void initMesh(const glm::vec3 &centerPosition, const float halfWidth, const float halfHeight);
  void initContourMesh(const glm::vec3 &centerPosition, const float halfWidth, const float halfHeight);
  void initProperties(const float width, const float height);
  void setSize(const float width, const float height);
};
