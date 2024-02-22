#pragma once
#include "ray.h"
#include "sceneObject.h"

enum class ElementType {
  // 3D
  SPHERE,
  CUBIC,
  CYLINDER,
  // 2D
  TRIANGLE,
  CIRCLE,
  SQUARE,
  LINE,
  POINT,
};

class SceneElementFactory {
public:
  static std::unique_ptr<SceneObject> createSceneObject(const Ray &ray, const float &distance, const ElementType primitiveType);
};
