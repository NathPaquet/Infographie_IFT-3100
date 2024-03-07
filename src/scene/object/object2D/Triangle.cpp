#include "Triangle.h"

Triangle::Triangle(const glm::vec3 &centerPosition, const glm::vec2 &firstPoint) {
  initMesh(centerPosition, firstPoint);
}

Triangle::Triangle(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
  auto vecFirst = outerPosition - centerPosition;
  glm::vec2 firstPoint = glm::vec2(vecFirst.x, vecFirst.y);
  initMesh(centerPosition, firstPoint);
}

void Triangle::drawPreview(const glm::vec3 &centerPosition, const glm::vec2 &firstPoint) {
  ofPrimitiveMode mode = OF_PRIMITIVE_TRIANGLES;
  std::vector<glm::vec3> vertices;
  // APROXIMATION VALID ONLY IF CAMERA IS LOOKING AT (0,0,1)
  auto vec1 = glm::vec3(1, 0, 0);
  auto vec2 = glm::vec3(0, 1, 0);

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

void Triangle::drawPreview(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
  ofPrimitiveMode mode = OF_PRIMITIVE_TRIANGLES;
  std::vector<glm::vec3> vertices;
  // APROXIMATION VALID ONLY IF CAMERA IS LOOKING AT (0,0,1)
  auto vec1 = glm::vec3(1, 0, 0);
  auto vec2 = glm::vec3(0, 1, 0);
  auto vecFirst = outerPosition - centerPosition;
  glm::vec2 firstPoint = glm::vec2(vecFirst.x, vecFirst.y);
  drawPreview(centerPosition, firstPoint);
}

void Triangle::initMesh(const glm::vec3 &centerPosition, const glm::vec2 &firstPoint) {
  ofPrimitiveMode mode = OF_PRIMITIVE_TRIANGLES;
  std::vector<glm::vec3> vertices;
  // APROXIMATION VALID ONLY IF CAMERA IS LOOKING AT (0,0,1)
  auto vec1 = glm::vec3(1, 0, 0);
  auto vec2 = glm::vec3(0, 1, 0);

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