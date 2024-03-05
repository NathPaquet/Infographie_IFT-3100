#include "Circle.h"

Circle::Circle(const Ray &ray, const float &distance) {
  std::vector<glm::vec3> vertices;
  // generating an orthogonal base from the ray vector
  auto u = glm::vec3(1, 0, 0);
  if (glm::dot(ray.getDirection(), u) != 0) {
    u = glm::vec3(0, 1, 0);
  }
  auto vec1 = glm::normalize(glm::cross(ray.getDirection(), u));
  auto vec2 = glm::normalize(glm::cross(vec1, ray.getDirection()));
  auto centerPosition = ray.getOrigin() + distance * ray.getDirection();
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

void Circle::drawDefaultPreview(const Ray &ray, const float &distance) {
  auto centerPosition = ray.getOrigin() + distance * ray.getDirection();
  ofDrawCircle(centerPosition, 20);
}
