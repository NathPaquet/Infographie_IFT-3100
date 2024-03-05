#include "Model3D.h"

#include "ofxAssimpModelLoader.h"

Model3D::Model3D(const Ray &ray, const float &distance) {
  // TODO find a way not to load mesh in this section !
  ofxAssimpModelLoader model;
  model.loadModel("druid.gltf", 20);
  auto position = ray.getOrigin() + ray.getDirection() * distance;
  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(model.getMesh(0)));
  this->primitive->setPosition(position);
  this->primitive->setScale(20);
}
