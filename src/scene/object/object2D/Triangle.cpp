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
  auto centerPosition = ray.getOrigin() + distance * ray.getDirection();

  glm::vec2 firstPoint = glm::vec2(20, 20);
  std::array<float, 4> values1 = {-0.5f,
      std::sqrt(3) / 2,
      -std::sqrt(3) / 2,
      -0.5f};

  auto rotate120deg = glm::make_mat2x2(values1.data());

  auto secondPoint = rotate120deg * firstPoint;
  auto thirdPoint = rotate120deg * secondPoint;

  vertices.emplace_back(firstPoint.x * vec1 + firstPoint.y * vec2);
  vertices.emplace_back(secondPoint.x * vec1 + secondPoint.y * vec2);
  vertices.emplace_back(thirdPoint.x * vec1 + thirdPoint.y * vec2);

  ofMesh mesh = ofMesh(OF_PRIMITIVE_TRIANGLES, vertices);
  mesh.addIndex(0);
  mesh.addIndex(1);
  mesh.addIndex(2);
  // auto mesh = ofMesh(OF_PRIMITIVE_TRIANGLES, vertices);
  // mesh.addNormal(ray.getDirection());
  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(mesh));
  this->primitive->setPosition(centerPosition);
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
  auto centerPosition = ray.getOrigin() + distance * ray.getDirection();

  glm::vec2 firstPoint = glm::vec2(20, 20);
  std::array<float, 4> values1 = {-0.5f,
      std::sqrt(3) / 2,
      -std::sqrt(3) / 2,
      -0.5f};

  auto rotate120deg = glm::make_mat2x2(values1.data());

  auto secondPoint = rotate120deg * firstPoint;
  auto thirdPoint = rotate120deg * secondPoint;

  vertices.emplace_back(centerPosition + firstPoint.x * vec1 + firstPoint.y * vec2);
  vertices.emplace_back(centerPosition + secondPoint.x * vec1 + secondPoint.y * vec2);
  vertices.emplace_back(centerPosition + thirdPoint.x * vec1 + thirdPoint.y * vec2);

  ofDrawTriangle(
      centerPosition + firstPoint.x * vec1 + firstPoint.y * vec2,
      centerPosition + secondPoint.x * vec1 + secondPoint.y * vec2,
      centerPosition + thirdPoint.x * vec1 + thirdPoint.y * vec2);
}
