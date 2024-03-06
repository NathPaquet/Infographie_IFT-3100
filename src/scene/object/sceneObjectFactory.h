#pragma once
#include "ray.h"
#include "sceneObject.h"

enum class ElementType {
  // 3D
  SPHERE,
  CUBIC,
  CYLINDER,
  MODEL3D,
  // 2D
  TRIANGLE,
  CIRCLE,
  SQUARE,
  LINE,
  STAR,
};

class SceneObjectFactory {
public:
  static std::unique_ptr<SceneObject> createDefaultSceneObject(const glm::vec3 &position, const ElementType primitiveType);
  static std::unique_ptr<SceneObject> createSceneObject(const glm::vec3 &centerPosition, const glm::vec3 &outerPosition, const ElementType primitiveType);
};
