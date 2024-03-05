#include "Star.h"

Star::Star(const glm::vec3 &centerPosition, const float radius = 20.f) {
  initMesh(centerPosition, radius);
}

Star::Star(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
  initMesh(centerPosition, glm::length(outerPosition - centerPosition));
}

void Star::drawPreview(const glm::vec3 &centerPosition, const float radius) {
}

void Star::drawPreview(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
}

void Star::initMesh(const glm::vec3 &centerPosition, const float radius) {
  std::vector<glm::vec3> vertices;
  // APROXIMATION VALID ONLY IF CAMERA IS LOOKING AT (0,0,1)
  auto vec1 = glm::vec3(1, 0, 0);
  auto vec2 = glm::vec3(0, 1, 0);

  auto minRadius = radius - this->diffRadius;
  vertices.push_back({0, 0, 0});

  glm::vec2 pointMax = {radius, 0};
  glm::vec2 pointMin = {minRadius, 0};
  vertices.push_back(pointMax.x * vec1 + pointMax.y * vec2);
  for (size_t i = 1; i < this->numberOfSection; i++) {
    pointMax = this->rotationMatrix * pointMax;
    pointMin = this->rotationMatrix * pointMin;

    if (i % 2 == 0) {
      vertices.push_back(pointMax.x * vec1 + pointMax.y * vec2);
    } else {
      vertices.push_back(pointMin.x * vec1 + pointMin.y * vec2);
    }
  }

  ofMesh mesh = ofMesh(OF_PRIMITIVE_TRIANGLES, vertices);

  for (int i = 0; i < this->numberOfSection; i++) {
    mesh.addIndex(i + 1);
    mesh.addIndex((i + 1) % this->numberOfSection + 1);
    mesh.addIndex(0);
  }
}
