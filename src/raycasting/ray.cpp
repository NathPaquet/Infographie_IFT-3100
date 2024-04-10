#include "Ray.h"

#include "constants.h"
#include "object/object2D/model/MagicSword.h"
#include "object/object2D/model/SpaceRocket.h"
#include "object/object2D/primitive/Circle.h"
#include "object/object2D/primitive/Line.h"
#include "object/object2D/primitive/Square.h"
#include "object/object2D/primitive/Star.h"
#include "object/object2D/primitive/Triangle.h"
#include "object/object2D/spline/catmullRomSpline.h"
#include "object/sceneObjectFactory.h"

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
  float distanceToTheClosestSurface = std::numeric_limits<float>::max();

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

void Ray::drawPrimitiveDefaultPreview(ElementType elementType, const glm::vec3 &centerPosition) {
  ofPushStyle();
  // draw origin
  ofSetColor((ImVec4)Constants::PRIMITIVE_PREVIEW_COLOR);
  // draw direction
  ofNoFill();
  switch (elementType) {
    case ElementType::CUBIC:
      ofDrawBox(centerPosition, 20.f, 20.f, 20.f);
      break;
    case ElementType::SPHERE:
      ofDrawSphere(centerPosition, 20.f);
      break;
    case ElementType::CYLINDER:
      ofDrawCylinder(centerPosition, 20.f, 20.f);
      break;
    case ElementType::TRIANGLE:
      Triangle::drawPreview(centerPosition);
      break;
    case ElementType::SQUARE:
      Square::drawPreview(centerPosition);
      break;
    case ElementType::CIRCLE:
      Circle::drawPreview(centerPosition);
      break;
    default:
      ofDrawSphere(centerPosition, 20.f);
      break;
  }
  ofPopStyle();
}

void Ray::drawPrimitivePreview(ElementType elementType, const glm::vec3 &centerPosition, const glm::vec3 &outerPosition) {
  ofPushStyle();
  // draw origin
  ofSetColor((ImVec4)Constants::PRIMITIVE_PREVIEW_COLOR);
  // draw direction
  ofNoFill();
  switch (elementType) {
    case ElementType::CUBIC:
      ofDrawBox(centerPosition, 20.f, 20.f, 20.f);
      break;
    case ElementType::SPHERE:
      ofDrawSphere(centerPosition, 20.f);
      break;
    case ElementType::CYLINDER:
      ofDrawCylinder(centerPosition, 20.f, 20.f);
      break;
    case ElementType::TRIANGLE:
      Triangle::drawPreview(centerPosition, outerPosition);
      break;
    case ElementType::SQUARE:
      Square::drawPreview(centerPosition, outerPosition);
      break;
    case ElementType::CIRCLE:
      Circle::drawPreview(centerPosition, outerPosition);
      break;
    case ElementType::STAR:
      Star::drawPreview(centerPosition, outerPosition);
      break;
    case ElementType::LINE:
      Line::drawPreview(centerPosition, outerPosition);
      break;
    case ElementType::CATMULL_ROM_SPLINE:
      CatmullRomSpline::drawPreview(centerPosition, outerPosition);
      break;
    case ElementType::SPACE_ROCKET:
      SpaceRocket::drawPreview(centerPosition, outerPosition);
      break;
    case ElementType::MAGIC_SWORD:
      MagicSword::drawPreview(centerPosition, outerPosition);
      break;
    default:
      ofDrawSphere(centerPosition, 20.f);
      break;
  }
  ofPopStyle();
}