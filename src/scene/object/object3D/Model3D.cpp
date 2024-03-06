#include "Model3D.h"

#include "ofxAssimpModelLoader.h"

Model3D::Model3D(const glm::vec3 &position) {
  // TODO find a way not to load mesh in this section !
  ofxAssimpModelLoader model;
  model.loadModel("druid.gltf", 20);
  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(model.getMesh(0)));
  this->primitive->setPosition(position);
  this->primitive->setScale(20);
}
