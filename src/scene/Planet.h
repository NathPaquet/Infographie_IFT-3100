#pragma once

#include "./layouts/ColorPicker.h"
#include "sceneObject.h"

class Planet : public SceneObject {
public:
  void draw() const override;
  void draw_properties() override;
  Planet(const float x, const float y, const float z);

private:
  void set_radius(const float radius);
  float radius = 20.f;
  ofMesh mainMesh;
  ofTexture mTex;
  ColorPicker colorPicker;
};
