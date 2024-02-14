#pragma once
#include "sceneObject.h"

enum class ElementType {
  SPHERE,
  CUBIC,
  CYLINDER
};

class SceneElementFactory {
public:
  static std::unique_ptr<SceneObject> createSceneObject(const ofVec3f &position, const ElementType primitiveType);
};
