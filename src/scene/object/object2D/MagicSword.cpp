#include "MagicSword.h"

#include "Triangle.h"
#include "object2D/Star.h"

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
  ofTranslate({0, -bladeHeight / 2 - handleHeight / 2, 0});

  Square::drawPreview({0, 0, 0}, width / 2, handleHeight / 2);

  ofTranslate({0, -handleHeight / 2 - longHandleHeight / 2, 0});

  Square::drawPreview({0, 0, 0}, bladeWidth / 2, longHandleHeight / 2);

  ofTranslate({0, -longHandleHeight / 2, 0});

  ofRotateDeg(360 / 10);
  Star::drawPreview(
      {0, 0, 0},
      bladeWidth);

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

  glm::vec3 temp_translation = centerPosition;
  auto blade = Square(temp_translation, bladeWidth / 2, bladeHeight / 2);
  auto head = Triangle(
      temp_translation + glm::vec3(0, bladeHeight / 2 + sqrt(3) * bladeWidth / 6, 0),
      temp_translation + glm::vec3(bladeWidth / 2, bladeHeight / 2, 0));

  temp_translation = temp_translation + glm::vec3(0, -bladeHeight / 2 - handleHeight / 2, 0);

  auto handle = Square(temp_translation, width / 2, handleHeight / 2);

  temp_translation = temp_translation + glm::vec3(0, -handleHeight / 2 - longHandleHeight / 2, 0);

  auto longHandle = Square(temp_translation, bladeWidth / 2, longHandleHeight / 2);

  temp_translation = temp_translation + glm::vec3(0, -longHandleHeight / 2, 0);

  auto star = Star(temp_translation, bladeWidth);

  std::vector<glm::vec3> vertices;
  for (auto &&vertex : blade.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(blade.getPrimitive().getPosition() + vertex);
  }
  for (auto &&vertex : head.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(head.getPrimitive().getPosition() + vertex);
  }
  for (auto &&vertex : handle.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(handle.getPrimitive().getPosition() + vertex);
  }
  for (auto &&vertex : longHandle.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(longHandle.getPrimitive().getPosition() + vertex);
  }
  for (auto &&vertex : star.getPrimitive().getMesh().getVertices()) {
    vertices.push_back(star.getPrimitive().getPosition() + vertex);
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
  this->position = centerPosition;
}
