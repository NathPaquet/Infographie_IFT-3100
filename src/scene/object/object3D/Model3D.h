#pragma once
#include "object/sceneObject.h"

#include <ray.h>

class Model3D : public SceneObject {
public:
	Model3D(const glm::vec3& position, const string& modelPath);

private:
	float initialScaleFactor;
	void set_size(const float size);
	void updateProperties() override;
};
