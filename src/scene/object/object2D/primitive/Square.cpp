#include "Square.h"

Square::Square(const glm::vec3 &centerPosition, const float halfWidth, const float halfHeight) {
  initProperties(halfWidth, halfHeight);
  initMesh(centerPosition, halfWidth, halfHeight);
}

Square::Square(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
  auto width = (outerPosition - centerPosition).x;
  auto height = (outerPosition - centerPosition).y;
  initProperties(width, height);
  initMesh(centerPosition, width, height);
}

void Square::drawPreview(const glm::vec3 &centerPosition, const float halfWidth, const float halfHeight) {
  ofDrawRectangle(centerPosition.x - halfWidth, centerPosition.y - halfHeight, centerPosition.z, halfWidth * 2, halfHeight * 2);
}

void Square::drawPreview(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
  auto width = (outerPosition - centerPosition).x;
  auto height = (outerPosition - centerPosition).y;
  drawPreview(centerPosition, width, height);
}

void Square::initMesh(const glm::vec3 &centerPosition, const float halfWidth, const float halfHeight) {
  std::vector<glm::vec3> vertices;
  // APROXIMATION VALID ONLY IF CAMERA IS LOOKING AT (0,0,1)
  auto vec1 = glm::vec3(1, 0, 0);
  auto vec2 = glm::vec3(0, 1, 0);
  vertices.emplace_back(halfWidth * vec1 + halfHeight * vec2);
  vertices.emplace_back(-halfWidth * vec1 + halfHeight * vec2);
  vertices.emplace_back(halfWidth * vec1 - halfHeight * vec2);
  vertices.emplace_back(-halfWidth * vec1 - halfHeight * vec2);

  ofMesh mesh = ofMesh(OF_PRIMITIVE_TRIANGLES, vertices);
  mesh.addIndex(0);
  mesh.addIndex(1);
  mesh.addIndex(2);
  mesh.addIndex(1);
  mesh.addIndex(2);
  mesh.addIndex(3);
  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(mesh));
  this->primitive->setPosition(centerPosition);
  this->position = centerPosition;
}

void Square::initContourMesh(const glm::vec3 &centerPosition, const float halfWidth, const float halfHeight) {
  std::vector<glm::vec3> vertices;
  // APROXIMATION VALID ONLY IF CAMERA IS LOOKING AT (0,0,1)
  auto vec1 = glm::vec3(1, 0, 0);
  auto vec2 = glm::vec3(0, 1, 0);
  vertices.emplace_back(halfWidth * vec1 + halfHeight * vec2);
  vertices.emplace_back(halfWidth * vec1 - halfHeight * vec2);
  vertices.emplace_back(-halfWidth * vec1 - halfHeight * vec2);
  vertices.emplace_back(-halfWidth * vec1 + halfHeight * vec2);

  ofMesh mesh = ofMesh(OF_PRIMITIVE_LINE_LOOP, vertices);
  for (int i = 0; i < 4; i++) {
    mesh.addIndex(i);
  }
  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(mesh));
  this->primitive->setPosition(centerPosition);
  this->position = centerPosition;
}

void Square::initProperties(const float width, const float height) {
  this->addProperty(PROPERTY_ID::WIDTH, width);
  this->addProperty(PROPERTY_ID::HEIGHT, height);
}

void Square::setSize(const float width, const float height) {
  initMesh(this->position, width, height);
}

void Square::updateProperties() {
  SceneObject::updateProperties();
  if (this->properties.at(PROPERTY_ID::WIDTH)->isValueChanged() || this->properties.at(PROPERTY_ID::HEIGHT)->isValueChanged() || this->properties.at(PROPERTY_ID::SHOW_WIREFRAME)->isValueChanged()) {
    const float width = this->getPropertyValue<float>(PROPERTY_ID::WIDTH);
    const float height = this->getPropertyValue<float>(PROPERTY_ID::HEIGHT);

    const bool showWireFrame = this->getPropertyValue<bool>(PROPERTY_ID::SHOW_WIREFRAME);

    showWireFrame ? initContourMesh(this->position, width, height) : setSize(width, height);
    this->properties.at(PROPERTY_ID::WIDTH)->setChanged(false);
    this->properties.at(PROPERTY_ID::HEIGHT)->setChanged(false);

    this->properties.at(PROPERTY_ID::SHOW_WIREFRAME)->setChanged(false);
  }
}
