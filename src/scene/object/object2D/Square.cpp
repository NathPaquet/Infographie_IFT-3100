#include "Square.h"
#include "constants.h"

Square::Square(const glm::vec3 &centerPosition) {
  std::vector<glm::vec3> vertices;
  // APROXIMATION VALID ONLY IF CAMERA IS LOOKING AT (0,0,1)
  auto vec1 = glm::vec3(1, 0, 0);
  auto vec2 = glm::vec3(0, 1, 0);

  vertices.emplace_back(10 * vec1 + 10 * vec2);
  vertices.emplace_back(-10 * vec1 + 10 * vec2);
  vertices.emplace_back(10 * vec1 - 10 * vec2);
  vertices.emplace_back(-10 * vec1 - 10 * vec2);

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

void Square::drawDefaultPreview(const glm::vec3 &centerPosition) {
  ofDrawRectangle(centerPosition.x-10,centerPosition.y-10, centerPosition.z, 20, 20);
}
