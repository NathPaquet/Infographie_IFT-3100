#pragma once
#include "ray.h"
#include "sceneObject.h"

enum class ElementType {
  // 3D primitives
  SPHERE,
  CUBIC,
  CYLINDER,
  // 2D primitives
  TRIANGLE,
  CIRCLE,
  SQUARE,
  LINE,
  POINT,
  // 3D models
  DRUID,
  FREDDY_PLUSH
};

class SceneObjectFactory {
public:
  static std::unique_ptr<SceneObject> createSceneObject(const Ray &ray, const float &distance, const ElementType primitiveType);
};
