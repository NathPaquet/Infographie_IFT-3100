#pragma once
#include "object/sceneObject.h"
#include "ofMain.h"
#include "raycasting/ray.h"
class Square : public SceneObject {
public:
  Square(const Ray &ray, const float &distance);
  static void drawDefaultPreview(const Ray &ray, const float &distance);
};
