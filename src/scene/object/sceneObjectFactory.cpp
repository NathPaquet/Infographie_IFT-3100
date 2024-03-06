#include "SceneObjectFactory.h"

#include "constants.h"
#include "object2D/Circle.h"
#include "object2D/Square.h"
#include "object2D/Triangle.h"
#include "object3D/CubicPlanet.h"
#include "object3D/CylinderPlanet.h"
#include "object3D/Model3D.h"
#include "object3D/Planet.h"

std::unique_ptr<SceneObject> SceneObjectFactory::createSceneObject(const Ray &ray, const float &distance, const ElementType primitiveType) {
  const ofVec3f position = ray.getOrigin() + ray.getDirection() * distance;
  switch (primitiveType) {
    case (ElementType::SPHERE):
      return std::make_unique<Planet>(Planet(position.x, position.y, position.z));
    case (ElementType::CUBIC):
      return std::make_unique<CubicPlanet>(CubicPlanet(position.x, position.y, position.z));
    case ElementType::CYLINDER:
      return std::make_unique<CylinderPlanet>(CylinderPlanet(position.x, position.y, position.z));
    case ElementType::DRUID:
      return std::make_unique<Model3D>(Model3D(ray, distance, Constants::DRUID_MODEL_PATH));
    case ElementType::FREDDY_PLUSH:
      return std::make_unique<Model3D>(Model3D(ray, distance, Constants::FREDDY_PLUSH_MODEL_PATH));
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
