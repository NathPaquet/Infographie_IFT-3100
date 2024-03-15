#include "MagicSword.h"

#include "primitive/Square.h"
#include "primitive/Star.h"
#include "primitive/Triangle.h"

MagicSword::MagicSword(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
  const auto width = abs((outerPosition - centerPosition).x);
  const auto height = abs((outerPosition - centerPosition).y);
  initMesh(centerPosition, width * 2, height * 2);
}

MagicSword::MagicSword(const glm::vec3 &centerPosition, const float width, const float height) {
  initMesh(centerPosition, width * 2, height * 2);
}

void MagicSword::drawPreview(const glm::vec3 &centerPosition, const float width, const float height) {
  // center position is the center of the body
  const float bladeWidth = width / 3;
  const float bladeHeight = height * 2 / 3;
  const float handleHeight = (height - bladeHeight) * 1 / 4;
  const float longHandleHeight = (height - bladeHeight) * 3 / 4;

  ofPushMatrix();
  ofTranslate(centerPosition);
  // blade
  Square::drawPreview({0, 0, 0}, bladeWidth / 2, bladeHeight / 2);
  // head
  Triangle::drawPreview(
      glm::vec3(0, bladeHeight / 2 + sqrt(3) * bladeWidth / 6, 0),
      glm::vec3(bladeWidth / 2, bladeHeight / 2, 0));
  // handle
  Square::drawPreview({0, -bladeHeight / 2 - handleHeight / 2, 0}, width / 2, handleHeight / 2);

  Square::drawPreview({0, -handleHeight - longHandleHeight / 2 - bladeHeight / 2, 0}, bladeWidth / 2, longHandleHeight / 2);

  Star::drawPreview({0, -handleHeight - longHandleHeight - bladeHeight / 2, 0}, bladeWidth);

  ofPopMatrix();
}

void MagicSword::drawPreview(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
  const auto width = abs((outerPosition - centerPosition).x);
  const auto height = abs((outerPosition - centerPosition).y);
  drawPreview(centerPosition, width * 2, height * 2);
}

void MagicSword::initMesh(const glm::vec3 &centerPosition, const float width, const float height) {
  // center position is the center of the body
  const float bladeWidth = width / 3;
  const float bladeHeight = height * 2 / 3;
  const float handleHeight = (height - bladeHeight) * 1 / 4;
  const float longHandleHeight = (height - bladeHeight) * 3 / 4;

  ofPushMatrix();
  ofTranslate(centerPosition);

  auto blade = Square({0, 0, 0}, bladeWidth / 2, bladeHeight / 2);
  auto head = Triangle(
      glm::vec3(0, bladeHeight / 2 + sqrt(3) * bladeWidth / 6, 0),
      glm::vec3(bladeWidth / 2, bladeHeight / 2, 0));

  auto handle = Square({0, -bladeHeight / 2 - handleHeight / 2, 0}, width / 2, handleHeight / 2);

  auto longHandle = Square({0, -handleHeight - longHandleHeight / 2 - bladeHeight / 2, 0}, bladeWidth / 2, longHandleHeight / 2);

  auto star = Star({0, -handleHeight - longHandleHeight - bladeHeight / 2, 0}, bladeWidth);

  ofPopMatrix();

  std::vector<glm::vec3> vertices;
  for (auto &&vertex : blade.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(glm::vec3(blade.getPrimitive().getPosition().x + vertex.x, blade.getPrimitive().getPosition().y + vertex.y, vertex.z));
  }
  for (auto &&vertex : head.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(glm::vec3(head.getPrimitive().getPosition().x + vertex.x, head.getPrimitive().getPosition().y + vertex.y, vertex.z));
  }
  for (auto &&vertex : handle.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(glm::vec3(handle.getPrimitive().getPosition().x + vertex.x, handle.getPrimitive().getPosition().y + vertex.y, vertex.z));
  }
  for (auto &&vertex : longHandle.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(glm::vec3(longHandle.getPrimitive().getPosition().x + vertex.x, longHandle.getPrimitive().getPosition().y + vertex.y, vertex.z));
  }
  for (auto &&vertex : star.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(glm::vec3(star.getPrimitive().getPosition().x + vertex.x, star.getPrimitive().getPosition().y + vertex.y, vertex.z));
  }

  ofMesh mesh = ofMesh(OF_PRIMITIVE_TRIANGLES, vertices);
  size_t totalIndexNumber = 0;
  for (auto &&index : blade.getPrimitive().getMesh().getIndices()) {
    mesh.addIndex(index + totalIndexNumber);
  }

  totalIndexNumber += blade.getPrimitive().getMesh().getVertices().size();
  for (auto &&index : head.getPrimitive().getMesh().getIndices()) {
    mesh.addIndex(index + totalIndexNumber);
  }

  totalIndexNumber += head.getPrimitive().getMesh().getVertices().size();
  for (auto &&index : handle.getPrimitive().getMesh().getIndices()) {
    mesh.addIndex(index + totalIndexNumber);
  }
  totalIndexNumber += handle.getPrimitive().getMesh().getVertices().size();

  for (auto &&index : longHandle.getPrimitive().getMesh().getIndices()) {
    mesh.addIndex(index + totalIndexNumber);
  }
  totalIndexNumber += longHandle.getPrimitive().getMesh().getVertices().size();

  for (auto &&index : star.getPrimitive().getMesh().getIndices()) {
    mesh.addIndex(index + totalIndexNumber);
  }

  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(mesh));
  this->primitive->setPosition(centerPosition);
  this->position = centerPosition;
}
