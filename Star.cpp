#include "Star.h"

const float ratioRadius = 0.6f;
const int numberOfSection = 10;
const float rotationPerVertex = 2 * glm::pi<float>() / numberOfSection;
const glm::mat2x2 rotationMatrix = glm::mat2x2(
    std::cos(rotationPerVertex), -std::sin(rotationPerVertex),
    std::sin(rotationPerVertex), std::cos(rotationPerVertex));

Star::Star(const glm::vec3 &centerPosition, const float radius) {
  initMesh(centerPosition, radius);
}

Star::Star(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
  initMesh(centerPosition, glm::length(outerPosition - centerPosition));
}

void Star::drawPreview(const glm::vec3 &centerPosition, const float radius) {
  std::vector<glm::vec3> vertices;
  // APROXIMATION VALID ONLY IF CAMERA IS LOOKING AT (0,0,1)
  auto vec1 = glm::vec3(1, 0, 0);
  auto vec2 = glm::vec3(0, 1, 0);

  auto minRadius = radius * ratioRadius;

  glm::vec2 pointMax = {radius, 0};
  glm::vec2 pointMin = {minRadius, 0};
  vertices.push_back(pointMax.x * vec1 + pointMax.y * vec2);
  for (size_t i = 1; i < numberOfSection; i++) {
    pointMax = rotationMatrix * pointMax;
    pointMin = rotationMatrix * pointMin;

    if (i % 2 == 0) {
      vertices.push_back(pointMax.x * vec1 + pointMax.y * vec2);
    } else {
      vertices.push_back(pointMin.x * vec1 + pointMin.y * vec2);
    }
  }
  for (size_t i = 0; i < numberOfSection; i++) {
    ofDrawLine(centerPosition + vertices[i], centerPosition + vertices[(i + 1) % numberOfSection]);
  }
}

void Star::drawPreview(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
  drawPreview(centerPosition, glm::length(outerPosition - centerPosition));
}

void Star::initMesh(const glm::vec3 &centerPosition, const float radius) {
  std::vector<glm::vec3> vertices;
  // APROXIMATION VALID ONLY IF CAMERA IS LOOKING AT (0,0,1)
  auto vec1 = glm::vec3(1, 0, 0);
  auto vec2 = glm::vec3(0, 1, 0);

  auto minRadius = radius * ratioRadius;
  vertices.push_back({0, 0, 0});

  glm::vec2 pointMax = {radius, 0};
  glm::vec2 pointMin = {minRadius, 0};
  vertices.push_back(pointMax.x * vec1 + pointMax.y * vec2);
  for (size_t i = 1; i < numberOfSection; i++) {
    pointMax = rotationMatrix * pointMax;
    pointMin = rotationMatrix * pointMin;

    if (i % 2 == 0) {
      vertices.push_back(pointMax.x * vec1 + pointMax.y * vec2);
    } else {
      vertices.push_back(pointMin.x * vec1 + pointMin.y * vec2);
    }
  }

  ofMesh mesh = ofMesh(OF_PRIMITIVE_TRIANGLES, vertices);

  for (int i = 0; i < numberOfSection; i++) {
    mesh.addIndex(i + 1);
    mesh.addIndex((i + 1) % numberOfSection + 1);
    mesh.addIndex(0);
  }

  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(mesh));
  this->primitive->setPosition(centerPosition);
}
