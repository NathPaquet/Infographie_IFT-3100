#pragma once
#include "glm/gtx/intersect.hpp"
#include "ofMain.h"

enum class ElementType;

class Ray {
public:
  Ray(){};
  Ray(glm::vec3 origin, glm::vec3 direction);
  void set(glm::vec3 origin, glm::vec3 direction);

  const glm::vec3 &getOrigin() const;
  const glm::vec3 &getDirection() const;
  bool isRayCollidingWithPrimitive(const of3dPrimitive &primitive, glm::vec2 &baricentricCoords, float &distance);
  void drawPrimitivePreview(ElementType elementType, const glm::vec3 &centerPosition, const glm::vec3 &outerPosition);
  void drawPrimitiveDefaultPreview(ElementType elementType, const glm::vec3 &centerPosition);

private:
  glm::vec3 origin;
  glm::vec3 direction;
};
