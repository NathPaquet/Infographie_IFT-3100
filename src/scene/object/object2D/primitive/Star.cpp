#include "Star.h"

const float radiusDefaultRatio = 0.6f;

Star::Star(const glm::vec3 &centerPosition, const float radius) {
  initProperties(radius, radiusDefaultRatio);
  initMesh(centerPosition, radius);
}

Star::Star(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
  initProperties(glm::length(outerPosition - centerPosition), radiusDefaultRatio);
  initMesh(centerPosition, glm::length(outerPosition - centerPosition));
}

void Star::drawPreview(const glm::vec3 &centerPosition, const float radius) {
  std::vector<glm::vec3> vertices;
  // APROXIMATION VALID ONLY IF CAMERA IS LOOKING AT (0,0,1)
  auto vec1 = glm::vec3(1, 0, 0);
  auto vec2 = glm::vec3(0, 1, 0);

  auto minRadius = radius * radiusDefaultRatio;

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
  for (int i = 0; i < numberOfSection; i++) {
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

  auto minRadius = radius * this->getPropertyValue<float>(PROPERTY_ID::RATIO);
  vertices.emplace_back(0, 0, 0);

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
  this->position = centerPosition;
}

void Star::initContourMesh(const glm::vec3 &centerPosition, const float radius) {
  std::vector<glm::vec3> vertices;
  // APROXIMATION VALID ONLY IF CAMERA IS LOOKING AT (0,0,1)
  auto vec1 = glm::vec3(1, 0, 0);
  auto vec2 = glm::vec3(0, 1, 0);

  auto minRadius = radius * this->getPropertyValue<float>(PROPERTY_ID::RATIO);

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
  ofMesh mesh = ofMesh(OF_PRIMITIVE_LINES, vertices);

  for (int i = 0; i < numberOfSection; i++) {
    mesh.addIndex(i);
    mesh.addIndex((i + 1) % numberOfSection);
  }

  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(mesh));
  this->primitive->setPosition(centerPosition);
  this->position = centerPosition;
}

void Star::initProperties(const float radius, const float ratio) {
  this->addProperty(PROPERTY_ID::RADIUS, radius);
  this->addProperty(PROPERTY_ID::RATIO, ratio);
}

void Star::setSize(const float radius) {
  initMesh(this->position, radius);
}

void Star::updateProperties() {
  Object2D::updateProperties();
  if (this->properties.at(PROPERTY_ID::RADIUS)->isValueChanged()
      || this->properties.at(PROPERTY_ID::RATIO)->isValueChanged()
      || this->properties.at(PROPERTY_ID::SHOW_WIREFRAME)->isValueChanged()) {
    const float radius = this->getPropertyValue<float>(PROPERTY_ID::RADIUS);
    const bool showWireFrame = this->getPropertyValue<bool>(PROPERTY_ID::SHOW_WIREFRAME);

    showWireFrame ? initContourMesh(this->position, radius) : setSize(radius);
    this->properties.at(PROPERTY_ID::RADIUS)->setChanged(false);
    this->properties.at(PROPERTY_ID::SHOW_WIREFRAME)->setChanged(false);
  }
}
