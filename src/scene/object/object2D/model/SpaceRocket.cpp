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
  ofTranslate(centerPosition);
  // body
  Square::drawPreview({0, 0, 0}, bodyWidth / 2, bodyHeight / 2);
  // sides
  Triangle::drawPreview(
      glm::vec3(-bodyWidth / 2 - rocketWidth / 2, -bodyHeight / 2 + rocketHeight, 0),
      glm::vec3(-bodyWidth / 2, -bodyHeight / 2, 0));

  Triangle::drawPreview(
      glm::vec3(bodyWidth / 2 + rocketWidth / 2, -bodyHeight / 2 + rocketHeight, 0),
      glm::vec3(bodyWidth / 2, -bodyHeight / 2, 0));
  // head
  Triangle::drawPreview(
      glm::vec3(0, bodyHeight / 2 + sqrt(3) * bodyWidth / 6, 0),
      glm::vec3(bodyWidth / 2, bodyHeight / 2, 0));
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

  auto rocketBody = Square(centerPosition, bodyWidth / 2, bodyHeight / 2);

  auto rocketLeft = Triangle(
      centerPosition + glm::vec3(-bodyWidth / 2 - rocketWidth / 2, -bodyHeight / 2 + rocketHeight, 0),
      centerPosition + glm::vec3(-bodyWidth / 2, -bodyHeight / 2, 0));

  auto rocketRight = Triangle(centerPosition + glm::vec3(bodyWidth / 2 + rocketWidth / 2, -bodyHeight / 2 + rocketHeight, 0),
      centerPosition + glm::vec3(bodyWidth / 2, -bodyHeight / 2, 0));

  auto rocketHead = Triangle(
      centerPosition + glm::vec3(0, bodyHeight / 2 + sqrt(3) * bodyWidth / 6, 0),
      centerPosition + glm::vec3(bodyWidth / 2, bodyHeight / 2, 0));

  std::vector<glm::vec3> vertices;
  for (auto &&vertex : rocketBody.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(rocketBody.getPrimitive().getPosition() + vertex);
  }
  for (auto &&vertex : rocketLeft.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(rocketLeft.getPrimitive().getPosition() + vertex);
  }
  for (auto &&vertex : rocketRight.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(rocketRight.getPrimitive().getPosition() + vertex);
  }
  for (auto &&vertex : rocketHead.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(rocketHead.getPrimitive().getPosition() + vertex);
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
  this->position = centerPosition;
}
