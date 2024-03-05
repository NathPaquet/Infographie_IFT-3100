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
  POINT,
};

class SceneObjectFactory {
public:
  static std::unique_ptr<SceneObject> createSceneObject(const Ray &ray, const float &distance, const glm::vec3 &position, const ElementType primitiveType);
};
