#include "SceneObjectFactory.h"

#include "SpaceRocket.h"
#include "constants.h"
#include "object2D/primitive/Circle.h"
#include "object2D/primitive/Line.h"
#include "object2D/primitive/Square.h"
#include "object2D/primitive/Star.h"
#include "object2D/primitive/Triangle.h"
#include "object3D/model/Model3D.h"
#include "object3D/primitive/CubicPlanet.h"
#include "object3D/primitive/CylinderPlanet.h"
#include "object3D/primitive/Planet.h"

std::unique_ptr<SceneObject> SceneObjectFactory::createDefaultSceneObject(const glm::vec3 &position, const ElementType primitiveType) {
  switch (primitiveType) {
    case (ElementType::SPHERE):
      return std::make_unique<Planet>(Planet(position.x, position.y, position.z));
    case (ElementType::CUBIC):
      return std::make_unique<CubicPlanet>(CubicPlanet(position.x, position.y, position.z));
    case ElementType::CYLINDER:
      return std::make_unique<CylinderPlanet>(CylinderPlanet(position.x, position.y, position.z));
    case ElementType::PLANET_EARTH:
      return std::make_unique<Model3D>(Model3D(position, Constants::PLANET_EARTH_MODEL_PATH));
    case ElementType::FREDDY_PLUSH:
      return std::make_unique<Model3D>(Model3D(position, Constants::FREDDY_PLUSH_MODEL_PATH));
    case ElementType::SPACE_SHIP:
      return std::make_unique<Model3D>(Model3D(position, Constants::SPACE_SHIP_MODEL_PATH));
    case ElementType::TRIANGLE:
      return std::make_unique<Triangle>(Triangle(position));
    case ElementType::SQUARE:
      return std::make_unique<Square>(Square(position));
    case ElementType::CIRCLE:
      return std::make_unique<Circle>(Circle(position));
    case ElementType::STAR:
      return std::make_unique<Star>(Star(position));
    case ElementType::SPACE_ROCKET:
      return std::make_unique<SpaceRocket>(SpaceRocket(position));
    default:
      return nullptr;
  }
}

std::unique_ptr<SceneObject> SceneObjectFactory::createSceneObject(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition, const ElementType primitiveType) {
  switch (primitiveType) {
    case (ElementType::SPHERE):
      return std::make_unique<Planet>(Planet(centerPosition.x, centerPosition.y, centerPosition.z));
    case (ElementType::CUBIC):
      return std::make_unique<CubicPlanet>(CubicPlanet(centerPosition.x, centerPosition.y, centerPosition.z));
    case ElementType::CYLINDER:
      return std::make_unique<CylinderPlanet>(CylinderPlanet(centerPosition.x, centerPosition.y, centerPosition.z));
    case ElementType::PLANET_EARTH:
      return std::make_unique<Model3D>(Model3D(centerPosition, Constants::PLANET_EARTH_MODEL_PATH));
    case ElementType::FREDDY_PLUSH:
      return std::make_unique<Model3D>(Model3D(centerPosition, Constants::FREDDY_PLUSH_MODEL_PATH));
    case ElementType::SPACE_SHIP:
      return std::make_unique<Model3D>(Model3D(centerPosition, Constants::SPACE_SHIP_MODEL_PATH));

    case ElementType::TRIANGLE:
      return std::make_unique<Triangle>(Triangle(centerPosition, outerPosition));
    case ElementType::SQUARE:
      return std::make_unique<Square>(Square(centerPosition, outerPosition));
    case ElementType::CIRCLE:
      return std::make_unique<Circle>(Circle(centerPosition, outerPosition));
    case ElementType::STAR:
      return std::make_unique<Star>(Star(centerPosition, outerPosition));
    case ElementType::LINE:
      return std::make_unique<Line>(Line(centerPosition, outerPosition));
    case ElementType::SPACE_ROCKET:
      return std::make_unique<SpaceRocket>(SpaceRocket(centerPosition, outerPosition));
    default:
      return nullptr;
  }
}
