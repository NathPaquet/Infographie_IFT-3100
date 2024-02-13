#pragma once
#include "sceneObject.h"

enum class ElementType {
  SPHERE,
  CUBIC
};

class SceneElementFactory {
public:
  static std::unique_ptr<SceneObject> createSceneObject(const ofVec3f &position, const ElementType primitiveType);
};
