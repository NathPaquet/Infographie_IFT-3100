#pragma once

#include "./layouts/ColorPicker.h"
#include "object/object3D/object3D.h"

#include <utils/ImageImporter.h>

class Planet : public Object3D {
public:
  Planet(const float x, const float y, const float z);

private:
  void setSize(const float radius);
  void updateProperties() override;
};
