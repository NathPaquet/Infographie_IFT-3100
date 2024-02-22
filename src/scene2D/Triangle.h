#pragma once
#include "ofMain.h"
#include "raycasting/ray.h"
#include "sceneObject.h"
class Triangle : public SceneObject {
public:
  Triangle(const Ray &ray, const float &distance);
  static void drawDefaultPreview(const Ray &ray, const float &distance);
};
