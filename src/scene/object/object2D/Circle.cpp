#include "Circle.h"

Circle::Circle(const glm::vec3 &centerPosition, const float radius) {
  initMesh(centerPosition, radius);
  initProperties(radius);
}

Circle::Circle(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
  auto radius = glm::length(outerPosition - centerPosition);
  initMesh(centerPosition, radius);
  initProperties(radius);
}

void Circle::drawPreview(const glm::vec3 &centerPosition, const float radius) {
  ofDrawCircle(centerPosition, radius);
}

void Circle::drawPreview(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
  ofDrawCircle(centerPosition, glm::length(outerPosition - centerPosition));
}

void Circle::initMesh(const glm::vec3 &centerPosition, const float radius) {
  std::vector<glm::vec3> vertices;
  // APROXIMATION VALID ONLY IF CAMERA IS LOOKING AT (0,0,1)
  auto vec1 = glm::vec3(1, 0, 0);
  auto vec2 = glm::vec3(0, 1, 0);

  vertices.push_back({0, 0, 0});

  glm::vec2 nextPoint = {radius, 0};
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
  this->position = centerPosition;
}

void Circle::initContourMesh(const glm::vec3 &centerPosition, const float radius) {
  std::vector<glm::vec3> vertices;
  // APROXIMATION VALID ONLY IF CAMERA IS LOOKING AT (0,0,1)
  auto vec1 = glm::vec3(1, 0, 0);
  auto vec2 = glm::vec3(0, 1, 0);

  glm::vec2 nextPoint = {radius, 0};
  vertices.push_back(nextPoint.x * vec1 + nextPoint.y * vec2);
  for (int i = 1; i < this->numberOfSection; i++) {
    nextPoint = this->rotationMatrix * nextPoint;
    vertices.push_back(nextPoint.x * vec1 + nextPoint.y * vec2);
  }

  ofMesh mesh = ofMesh(OF_PRIMITIVE_LINES, vertices);

  for (int i = 0; i < this->numberOfSection; i++) {
    mesh.addIndex(i);
    mesh.addIndex((i + 1) % this->numberOfSection);
  }

  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(mesh));
  this->primitive->setPosition(centerPosition);
  this->position = centerPosition;
}

void Circle::initProperties(const float radius) {
  this->addProperty(PROPERTY_ID::RADIUS, radius);
}

void Circle::setSize(const float radius) {
  initMesh(this->position, radius);
}

void Circle::updateProperties() {
  SceneObject::updateProperties();
  if (this->properties.at(PROPERTY_ID::RADIUS)->isValueChanged() || this->properties.at(PROPERTY_ID::SHOW_WIREFRAME)->isValueChanged()) {
    const float radius = this->getPropertyValue<float>(PROPERTY_ID::RADIUS);
    const bool showWireFrame = this->getPropertyValue<bool>(PROPERTY_ID::SHOW_WIREFRAME);

    showWireFrame ? initContourMesh(this->position, radius) : setSize(radius);
    this->properties.at(PROPERTY_ID::RADIUS)->setChanged(false);
    this->properties.at(PROPERTY_ID::SHOW_WIREFRAME)->setChanged(false);
  }
}
