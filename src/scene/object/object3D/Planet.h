#pragma once

#include "./layouts/ColorPicker.h"
#include "object/sceneObject.h"

#include <utils/ImageImporter.h>

class Planet : public SceneObject {
public:
  Planet(const float x, const float y, const float z);

private:
  void setSize(const float radius);
  void updateProperties() override;
};
