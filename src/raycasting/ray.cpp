#include "Ray.h"

#include "SceneElementFactory.h"

#include <scene2D/Triangle.h>

Ray::Ray(glm::vec3 origin, glm::vec3 direction) {
  this->origin = origin;
  this->direction = glm::normalize(direction);
}

void Ray::set(glm::vec3 origin, glm::vec3 direction) {
  this->origin = origin;
  this->direction = glm::normalize(direction);
}

const glm::vec3 &Ray::getOrigin() const {
  return this->origin;
}

const glm::vec3 &Ray::getDirection() const {
  return this->direction;
}

bool Ray::isRayCollidingWithPrimitive(const of3dPrimitive &primitive, glm::vec2 &baricentricCoords, float &distance) {
  bool found = false;
  float distanceToTheClosestSurface = numeric_limits<float>::max();
  for (auto &&face : primitive.getMesh().getUniqueFaces()) {
    bool intersection = glm::intersectRayTriangle(
        origin,
        direction,
        glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(0), 1.f)),
        glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(1), 1.f)),
        glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(2), 1.f)),
        baricentricCoords,
        distance);
    if (intersection && distance < distanceToTheClosestSurface) {
      found = true;
      distanceToTheClosestSurface = distance;
    }
  }
  distance = distanceToTheClosestSurface;
  return found;
}

void Ray::drawPrimitivePreview(const ofColor &color, ElementType elementType, float distance) {
  ofPushStyle();
  // draw origin
  ofSetColor(color);
  // draw direction
  auto end = this->origin + (this->direction * (distance));
  switch (elementType) {
    case ElementType::CUBIC:
      ofDrawBox(end, 20.f, 20.f, 20.f);
      break;
    case ElementType::SPHERE:
      ofDrawSphere(end, 20.f);
      break;
    case ElementType::CYLINDER:
      ofDrawCylinder(end, 20.f, 20.f);
      break;
    case ElementType::TRIANGLE:
      Triangle::drawDefaultPreview(*this, distance);
      break;
    default:
      ofDrawSphere(end, 20.f);
      break;
  }
  ofPopStyle();
}