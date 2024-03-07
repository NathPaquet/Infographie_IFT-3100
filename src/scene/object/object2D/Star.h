#pragma once
#include "object/sceneObject.h"

class Star : public SceneObject {
public:
  Star(const glm::vec3 &centerPosition, const float radius = 20.f);
  Star(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition);

  static void drawPreview(const glm::vec3 &centerPosition, const float radius = 20.f);
  static void drawPreview(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition);

private:
  void initMesh(const glm::vec3 &centerPosition, const float radius);
  void initContourMesh(const glm::vec3 &centerPosition, const float radius);
  void initProperties(const float radius, const float ratio);
  void setSize(const float radius);
  void updateProperties() override;
};
