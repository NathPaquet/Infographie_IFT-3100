#include "Triangle.h"

Triangle::Triangle(const Ray &ray, const float &distance) {
  ofPrimitiveMode mode = OF_PRIMITIVE_TRIANGLES;
  std::vector<glm::vec3> vertices;
  // generating an orthogonal base from the ray vector
  auto u = glm::vec3(1, 0, 0);
  if (glm::dot(ray.getDirection(), u) != 0) {
    u = glm::vec3(0, 1, 0);
  }
  auto vec1 = glm::normalize(glm::cross(ray.getDirection(), u));
  auto vec2 = glm::normalize(glm::cross(vec1, ray.getDirection()));

  vertices.emplace_back(ray.getOrigin() + distance * ray.getDirection() + 20 * vec1 + 20 * vec2);
  vertices.emplace_back(ray.getOrigin() + distance * ray.getDirection() - 20 * vec1 + 20 * vec2);
  vertices.emplace_back(ray.getOrigin() + distance * ray.getDirection() - 20 * vec1 - 20 * vec2);

  auto mesh = ofMesh(OF_PRIMITIVE_TRIANGLES, vertices);
  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(mesh));
}

void Triangle::drawDefaultPreview(const Ray &ray, const float &distance) {
  ofPrimitiveMode mode = OF_PRIMITIVE_TRIANGLES;
  std::vector<glm::vec3> vertices;
  // generating an orthogonal base from the ray vector
  auto u = glm::vec3(1, 0, 0);
  if (glm::dot(ray.getDirection(), u) != 0) {
    u = glm::vec3(0, 1, 0);
  }
  auto vec1 = glm::normalize(glm::cross(ray.getDirection(), u));
  auto vec2 = glm::normalize(glm::cross(vec1, ray.getDirection()));

  ofDrawTriangle(
      ray.getOrigin() + distance * ray.getDirection() + 20 * vec1 + 20 * vec2,
      ray.getOrigin() + distance * ray.getDirection() - 20 * vec1 + 20 * vec2,
      ray.getOrigin() + distance * ray.getDirection() - 20 * vec1 - 20 * vec2);
}
