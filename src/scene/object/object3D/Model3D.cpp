#include "Model3D.h"

#include <ofxAssimpModelLoader.h>

Model3D::Model3D(const Ray &ray, const float &distance, const string &modelPath) {
  // TODO : find a way not to load mesh in this section !
  ofxAssimpModelLoader model;
  ofLogNotice() << "Model3D::Model3D - loading model ... ";
  model.load(modelPath, ofxAssimpModelLoader::OPTIMIZE_DEFAULT);
  ofLogNotice() << "Model3D::Model3D - model loaded";
  ofLogNotice() << "Model3D::Model3D - Number of mesh : " << model.getMeshCount();
  auto position = ray.getOrigin() + ray.getDirection() * distance;
  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(model.getMesh(0)));
  this->primitive->setPosition(position);
  this->primitive->setScale(20);
}
