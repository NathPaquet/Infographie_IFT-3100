#pragma once
#include "object/object2D/Object2D.h"

const int numberOfSection = 10;
const float rotationPerVertex = 2 * glm::pi<float>() / numberOfSection;
const glm::mat2x2 rotationMatrix = glm::mat2x2(
    std::cos(rotationPerVertex), -std::sin(rotationPerVertex),
    std::sin(rotationPerVertex), std::cos(rotationPerVertex));

class Star : public Object2D {
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
