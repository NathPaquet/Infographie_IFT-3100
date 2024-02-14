#include "SceneElementFactory.h"

#include "..\..\CylinderPlanet.h"
#include "CubicPlanet.h"
#include "Planet.h"

std::unique_ptr<SceneObject> SceneElementFactory::createSceneObject(const ofVec3f &position, const ElementType primitiveType) {
  switch (primitiveType) {
    case (ElementType::SPHERE):
      return std::make_unique<Planet>(Planet(position.x, position.y, position.z));
    case (ElementType::CUBIC):
      return std::make_unique<CubicPlanet>(CubicPlanet(position.x, position.y, position.z));
    case ElementType::CYLINDER:
      return std::make_unique<CylinderPlanet>(CylinderPlanet(position.x, position.y, position.z));
  }
}
