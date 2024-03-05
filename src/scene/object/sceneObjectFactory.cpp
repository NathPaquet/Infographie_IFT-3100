#include "SceneObjectFactory.h"

#include "object2D/Circle.h"
#include "object2D/Square.h"
#include "object2D/Triangle.h"
#include "object3D/CubicPlanet.h"
#include "object3D/CylinderPlanet.h"
#include "object3D/Planet.h"
#include "object3D/Model3D.h"


std::unique_ptr<SceneObject> SceneObjectFactory::createSceneObject(const Ray &ray, const float &distance, const glm::vec3 &position, const ElementType primitiveType) {
  switch (primitiveType) {
    case (ElementType::SPHERE):
      return std::make_unique<Planet>(Planet(position.x, position.y, position.z));
    case (ElementType::CUBIC):
      return std::make_unique<CubicPlanet>(CubicPlanet(position.x, position.y, position.z));
    case ElementType::CYLINDER:
      return std::make_unique<CylinderPlanet>(CylinderPlanet(position.x, position.y, position.z));
    case ElementType::MODEL3D:
      return std::make_unique<Model3D>(Model3D(ray, distance));
    case ElementType::TRIANGLE:
      return std::make_unique<Triangle>(Triangle(ray, position));
    case ElementType::SQUARE:
      return std::make_unique<Square>(Square(position));
    case ElementType::CIRCLE:
      return std::make_unique<Circle>(Circle(position));
    default:
      return nullptr;
  }
}
