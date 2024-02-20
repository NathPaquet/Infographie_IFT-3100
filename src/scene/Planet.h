#pragma once

#include "./layouts/ColorPicker.h"
#include "sceneObject.h"

#include <utils/ImageImporter.h>

class Planet : public SceneObject {
public:
  Planet(const float x, const float y, const float z);

private:
  void updatePrimitive();
  void updateProperties() override;
};
