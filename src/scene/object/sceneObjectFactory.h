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
	STAR,
	POINT,
	// 3D models
	DRUID,
	FREDDY_PLUSH,
	SPACE_SHIP,
};

class SceneObjectFactory {
public:
	static std::unique_ptr<SceneObject> createDefaultSceneObject(const glm::vec3& position, const ElementType primitiveType);
	static std::unique_ptr<SceneObject> createSceneObject(const glm::vec3& centerPosition, const glm::vec3& outerPosition, const ElementType primitiveType);
};
