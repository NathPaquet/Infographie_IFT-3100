#include "SceneElementFactory.h"

#include "CubicPlanet.h"
#include "CylinderPlanet.h"
#include "Planet.h"
#include "scene2D/Circle.h"
#include "scene2D/Square.h"
#include "scene2D/Triangle.h"

std::unique_ptr<SceneObject> SceneElementFactory::createSceneObject(const Ray &ray, const float &distance, const ElementType primitiveType) {
  const ofVec3f position = ray.getOrigin() + ray.getDirection() * distance;
  switch (primitiveType) {
    case (ElementType::SPHERE):
      return std::make_unique<Planet>(Planet(position.x, position.y, position.z));
    case (ElementType::CUBIC):
      return std::make_unique<CubicPlanet>(CubicPlanet(position.x, position.y, position.z));
    case ElementType::CYLINDER:
      return std::make_unique<CylinderPlanet>(CylinderPlanet(position.x, position.y, position.z));
    case ElementType::TRIANGLE:
      return std::make_unique<Triangle>(Triangle(ray, distance));
    case ElementType::SQUARE:
      return std::make_unique<Square>(Square(ray, distance));
    case ElementType::CIRCLE:
      return std::make_unique<Circle>(Circle(ray, distance));
    default:
      return nullptr;
  }
}
