#include "SceneObjectFactory.h"

#include "constants.h"
#include "object2D/model/MagicSword.h"
#include "object2D/model/SpaceRocket.h"
#include "object2D/primitive/Circle.h"
#include "object2D/primitive/Line.h"
#include "object2D/primitive/Square.h"
#include "object2D/primitive/Star.h"
#include "object2D/primitive/Triangle.h"
#include "object2D/spline/catmullRomSpline.h"
#include "object3D/Camera.h"
#include "object3D/lights/types/DirectionalLight.h"
#include "object3D/model/Model3D.h"
#include "object3D/primitive/CubicPlanet.h"
#include "object3D/primitive/CylinderPlanet.h"
#include "object3D/primitive/Planet.h"

#include <lights/types/PointLight.h>
#include <lights/types/SpotLight.h>

std::unique_ptr<SceneObject> SceneObjectFactory::createDefaultSceneObject(const glm::vec3 &position, const ElementType primitiveType) {
  switch (primitiveType) {
    case (ElementType::SPHERE):
      return std::make_unique<Planet>(position.x, position.y, position.z);
    case (ElementType::CUBIC):
      return std::make_unique<CubicPlanet>(position.x, position.y, position.z);
    case ElementType::CYLINDER:
      return std::make_unique<CylinderPlanet>(position.x, position.y, position.z);
    case ElementType::POINT_LIGHT:
      return std::make_unique<PointLight>(position);
    case ElementType::DIRECTIONAL_LIGHT:
      return std::make_unique<DirectionalLight>(position);
    case ElementType::SPOT_LIGHT:
      return std::make_unique<SpotLight>(position);
    case ElementType::PLANET_EARTH:
      return std::make_unique<Model3D>(position, Constants::PLANET_EARTH_MODEL_PATH);
    case ElementType::FREDDY_PLUSH:
      return std::make_unique<Model3D>(position, Constants::FREDDY_PLUSH_MODEL_PATH);
    case ElementType::SPACE_SHIP:
      return std::make_unique<Model3D>(position, Constants::SPACE_SHIP_MODEL_PATH);
    case ElementType::CAMERA:
      return std::make_unique<Camera>(position);
    case ElementType::TRIANGLE:
      return std::make_unique<Triangle>(position);
    case ElementType::SQUARE:
      return std::make_unique<Square>(position);
    case ElementType::CIRCLE:
      return std::make_unique<Circle>(position);
    case ElementType::STAR:
      return std::make_unique<Star>(position);
    case ElementType::SPACE_ROCKET:
      return std::make_unique<SpaceRocket>(position);
    case ElementType::MAGIC_SWORD:
      return std::make_unique<MagicSword>(position);
    default:
      return nullptr;
  }
}

std::unique_ptr<SceneObject> SceneObjectFactory::createSceneObject(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition, const ElementType primitiveType) {
  float size;
  switch (primitiveType) {
    case (ElementType::SPHERE):
      return std::make_unique<Planet>(centerPosition.x, centerPosition.y, centerPosition.z);
    case (ElementType::CUBIC):
      size = 2 * abs(outerPosition.x - centerPosition.x);
      return std::make_unique<CubicPlanet>(centerPosition.x, centerPosition.y, centerPosition.z, size);
    case ElementType::CYLINDER:
      return std::make_unique<CylinderPlanet>(centerPosition.x, centerPosition.y, centerPosition.z);
    case ElementType::PLANET_EARTH:
      return std::make_unique<Model3D>(centerPosition, Constants::PLANET_EARTH_MODEL_PATH);
    case ElementType::FREDDY_PLUSH:
      return std::make_unique<Model3D>(centerPosition, Constants::FREDDY_PLUSH_MODEL_PATH);
    case ElementType::SPACE_SHIP:
      return std::make_unique<Model3D>(centerPosition, Constants::SPACE_SHIP_MODEL_PATH);
    case ElementType::POINT_LIGHT:
      return std::make_unique<PointLight>(centerPosition);
    case ElementType::TRIANGLE:
      return std::make_unique<Triangle>(centerPosition, outerPosition);
    case ElementType::SQUARE:
      return std::make_unique<Square>(centerPosition, outerPosition);
    case ElementType::CIRCLE:
      return std::make_unique<Circle>(centerPosition, outerPosition);
    case ElementType::STAR:
      return std::make_unique<Star>(centerPosition, outerPosition);
    case ElementType::LINE:
      return std::make_unique<Line>(centerPosition, outerPosition);
    case ElementType::CATMULL_ROM_SPLINE:
      return std::make_unique<CatmullRomSpline>(centerPosition, outerPosition);
    case ElementType::SPACE_ROCKET:
      return std::make_unique<SpaceRocket>(centerPosition, outerPosition);
    case ElementType::MAGIC_SWORD:
      return std::make_unique<MagicSword>(centerPosition, outerPosition);
    default:
      return nullptr;
  }
}
