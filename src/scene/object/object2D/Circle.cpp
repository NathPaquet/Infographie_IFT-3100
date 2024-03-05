#include "Circle.h"

Circle::Circle(const glm::vec3 &centerPosition) {
  std::vector<glm::vec3> vertices;
  // APROXIMATION VALID ONLY IF CAMERA IS LOOKING AT (0,0,1)
  auto vec1 = glm::vec3(1, 0, 0);
  auto vec2 = glm::vec3(0, 1, 0);

  vertices.push_back({0, 0, 0});

  glm::vec2 nextPoint = {20, 0};
  vertices.push_back(nextPoint.x * vec1 + nextPoint.y * vec2);
  for (int i = 1; i < this->numberOfSection; i++) {
    nextPoint = this->rotationMatrix * nextPoint;
    vertices.push_back(nextPoint.x * vec1 + nextPoint.y * vec2);
  }
  ofMesh mesh = ofMesh(OF_PRIMITIVE_TRIANGLES, vertices);

  for (int i = 0; i < this->numberOfSection; i++) {
    mesh.addIndex(i + 1);
    mesh.addIndex((i + 1) % this->numberOfSection + 1);
    mesh.addIndex(0);
  }

  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(mesh));
  this->primitive->setPosition(centerPosition);
}

void Circle::drawDefaultPreview(const glm::vec3 &centerPosition) {
  ofDrawCircle(centerPosition, 20);
}
