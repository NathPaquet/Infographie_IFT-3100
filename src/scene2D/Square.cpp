#include "Square.h"

Square::Square(const Ray &ray, const float &distance) {
  std::vector<glm::vec3> vertices;
  // generating an orthogonal base from the ray vector
  auto u = glm::vec3(1, 0, 0);
  if (glm::dot(ray.getDirection(), u) != 0) {
    u = glm::vec3(0, 1, 0);
  }
  auto vec1 = glm::normalize(glm::cross(ray.getDirection(), u));
  auto vec2 = glm::normalize(glm::cross(vec1, ray.getDirection()));
  auto centerPosition = ray.getOrigin() + distance * ray.getDirection();

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

void Square::drawDefaultPreview(const Ray &ray, const float &distance) {
  auto centerPosition = ray.getOrigin() + distance * ray.getDirection();
  ofDrawRectangle(centerPosition, 20, 20);
}
