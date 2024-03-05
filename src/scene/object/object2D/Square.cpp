#include "Square.h"
#include "constants.h"

Square::Square(const glm::vec3 &centerPosition, const float halfSize) {
  initMesh(centerPosition, halfSize);
}

Square::Square(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
  initMesh(centerPosition, sqrt(0.5f) * glm::length(outerPosition - centerPosition));
}

void Square::drawPreview(const glm::vec3 &centerPosition, const float halfSize) {
  ofDrawRectangle(centerPosition.x - halfSize, centerPosition.y - halfSize, centerPosition.z, halfSize * 2, halfSize * 2);
}

void Square::drawPreview(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
  drawPreview(centerPosition, sqrt(0.5f) * glm::length(outerPosition - centerPosition));
}

void Square::initMesh(const glm::vec3 &centerPosition,  const float halfSize) {
  std::vector<glm::vec3> vertices;
  // APROXIMATION VALID ONLY IF CAMERA IS LOOKING AT (0,0,1)
  auto vec1 = glm::vec3(1, 0, 0);
  auto vec2 = glm::vec3(0, 1, 0);
  vertices.emplace_back(halfSize * vec1 + halfSize * vec2);
  vertices.emplace_back(-halfSize * vec1 + halfSize * vec2);
  vertices.emplace_back(halfSize * vec1 - halfSize * vec2);
  vertices.emplace_back(-halfSize * vec1 - halfSize * vec2);
  
  ofMesh mesh = ofMesh(OF_PRIMITIVE_TRIANGLES, vertices);
  mesh.addIndex(0);
  mesh.addIndex(1);
  mesh.addIndex(2);
  mesh.addIndex(1);
  mesh.addIndex(2);
  mesh.addIndex(3);
  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(mesh));
  this->primitive->setPosition(centerPosition);
}
