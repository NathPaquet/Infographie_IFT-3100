#include "SpaceRocket.h"

#include "primitive/Square.h"
#include "primitive/Triangle.h"

SpaceRocket::SpaceRocket(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
  const auto width = abs((outerPosition - centerPosition).x);
  const auto height = abs((outerPosition - centerPosition).y);
  initMesh(centerPosition, width * 2, height * 2);
}

SpaceRocket::SpaceRocket(const glm::vec3 &centerPosition, const float width, const float height) {
  initMesh(centerPosition, width * 2, height * 2);
}

void SpaceRocket::drawPreview(const glm::vec3 &centerPosition, const float width, const float height) {
  // center position is the center of the body
  const float rocketWidth = width / 8;
  const float rocketHeight = sqrt(3) * rocketWidth / 2;

  const float headHeight = height / 3;
  const float bodyWidth = width - 2 * rocketWidth;
  const float bodyHeight = height - headHeight;

  ofPushMatrix();
  ofTranslate(centerPosition.x, centerPosition.y);

  // body
  Square::drawPreview({0, 0, centerPosition.z}, bodyWidth / 2, bodyHeight / 2);
  // sides
  Triangle::drawPreview(
      glm::vec3(-bodyWidth / 2 - rocketWidth / 2, -bodyHeight / 2 + rocketHeight, centerPosition.z),
      glm::vec3(-bodyWidth / 2, -bodyHeight / 2, centerPosition.z));

  Triangle::drawPreview(
      glm::vec3(bodyWidth / 2 + rocketWidth / 2, -bodyHeight / 2 + rocketHeight, centerPosition.z),
      glm::vec3(bodyWidth / 2, -bodyHeight / 2, centerPosition.z));

  // head
  Triangle::drawPreview(
      glm::vec3(0, bodyHeight / 2 + sqrt(3) * bodyWidth / 6, centerPosition.z),
      glm::vec3(bodyWidth / 2, bodyHeight / 2, centerPosition.z));

  ofPopMatrix();
}

void SpaceRocket::drawPreview(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
  const auto width = abs((outerPosition - centerPosition).x);
  const auto height = abs((outerPosition - centerPosition).y);
  drawPreview(centerPosition, width * 2, height * 2);
}

void SpaceRocket::initMesh(const glm::vec3 &centerPosition, const float width, const float height) {
  // center position is the center of the body
  const float rocketWidth = width / 8;
  const float rocketHeight = sqrt(3) * rocketWidth / 2;

  const float headHeight = height / 3;
  const float bodyWidth = width - 2 * rocketWidth;
  const float bodyHeight = height - headHeight;

  ofPushMatrix();
  ofTranslate(centerPosition.x, centerPosition.y);

  auto rocketBody = Square({0, 0, centerPosition.z}, bodyWidth / 2, bodyHeight / 2);

  auto rocketLeft = Triangle(
      glm::vec3(-bodyWidth / 2 - rocketWidth / 2, -bodyHeight / 2 + rocketHeight, centerPosition.z),
      glm::vec3(-bodyWidth / 2, -bodyHeight / 2, centerPosition.z));

  auto rocketRight = Triangle(
      glm::vec3(bodyWidth / 2 + rocketWidth / 2, -bodyHeight / 2 + rocketHeight, centerPosition.z),
      glm::vec3(bodyWidth / 2, -bodyHeight / 2, centerPosition.z));

  auto rocketHead = Triangle(
      glm::vec3(0, bodyHeight / 2 + sqrt(3) * bodyWidth / 6, centerPosition.z),
      glm::vec3(bodyWidth / 2, bodyHeight / 2, centerPosition.z));

  ofPopMatrix();

  std::vector<glm::vec3> vertices;
  for (auto &&vertex : rocketBody.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(glm::vec3(rocketBody.getPrimitive().getPosition().x + vertex.x, rocketBody.getPrimitive().getPosition().y + vertex.y, vertex.z));
  }
  for (auto &&vertex : rocketLeft.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(glm::vec3(rocketLeft.getPrimitive().getPosition().x + vertex.x, rocketLeft.getPrimitive().getPosition().y + vertex.y, vertex.z));
  }
  for (auto &&vertex : rocketRight.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(glm::vec3(rocketRight.getPrimitive().getPosition().x + vertex.x, rocketRight.getPrimitive().getPosition().y + vertex.y, vertex.z));
  }
  for (auto &&vertex : rocketHead.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(glm::vec3(rocketHead.getPrimitive().getPosition().x + vertex.x, rocketHead.getPrimitive().getPosition().y + vertex.y, vertex.z));
  }

  ofMesh mesh = ofMesh(OF_PRIMITIVE_TRIANGLES, vertices);

  size_t totalIndexNumber = 0;
  for (auto &&index : rocketBody.getPrimitive().getMesh().getIndices()) {
    mesh.addIndex(index + totalIndexNumber);
  }

  totalIndexNumber += rocketBody.getPrimitive().getMesh().getVertices().size();
  for (auto &&index : rocketLeft.getPrimitive().getMesh().getIndices()) {
    mesh.addIndex(index + totalIndexNumber);
  }

  totalIndexNumber += rocketLeft.getPrimitive().getMesh().getVertices().size();
  for (auto &&index : rocketRight.getPrimitive().getMesh().getIndices()) {
    mesh.addIndex(index + totalIndexNumber);
  }

  totalIndexNumber += rocketRight.getPrimitive().getMesh().getVertices().size();
  for (auto &&index : rocketHead.getPrimitive().getMesh().getIndices()) {
    mesh.addIndex(index + totalIndexNumber);
  }

  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(mesh));
  this->primitive->setPosition(centerPosition);
  this->position = centerPosition;
}
