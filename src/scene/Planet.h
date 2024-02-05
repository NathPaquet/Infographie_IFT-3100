#pragma once

#include "sceneObject.h"

class Planet : public SceneObject {
public:
	void draw() const;
	Planet(const float x, const float y, const float z);
};
