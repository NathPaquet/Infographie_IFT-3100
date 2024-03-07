#include "Line.h"

Line::Line(const glm::vec3 &startPoint, const glm::vec3 &endPoint) {
  this->endPoint = endPoint;
  this->startPoint = startPoint;
  initMesh(startPoint, endPoint);
}

void Line::drawPreview(const glm::vec3 &startPoint, const glm::vec3 &endPoint) {
  ofDrawLine(startPoint, endPoint);
}

void Line::initMesh(const glm::vec3 &startPoint, const glm::vec3 &endPoint) {
  std::vector<glm::vec3> vertices;
  // APROXIMATION VALID ONLY IF CAMERA IS LOOKING AT (0,0,1)
  auto vec1 = glm::vec3(1, 0, 0);
  auto vec2 = glm::vec3(0, 1, 0);

  vertices.push_back({0, 0, 0});
  vertices.push_back(endPoint - startPoint);

  ofMesh mesh = ofMesh(OF_PRIMITIVE_LINES, vertices);

  mesh.addIndex(0);
  mesh.addIndex(1);

  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(mesh));
  this->primitive->setPosition(startPoint);
}
