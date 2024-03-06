#include "Model3D.h"

#include <ofxAssimpModelLoader.h>

constexpr float DEFAULT_SIZE = 40.0f;

Model3D::Model3D(const Ray &ray, const float &distance, const string &modelPath) {
  this->addProperty<float>(PROPERTY_ID::SIZE, DEFAULT_SIZE);
  // TODO : find a way not to load mesh in this section !

  ofxAssimpModelLoader model;
  model.load(modelPath, ofxAssimpModelLoader::OPTIMIZE_DEFAULT);
  auto position = ray.getOrigin() + ray.getDirection() * distance;
  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(model.getMesh(0)));

  model.setScaleNormalization(false);
  ofMesh mesh = model.getMesh(0);

  auto xExtremes = minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(),
      [](const ofPoint &lhs, const ofPoint &rhs) {
        return lhs.x < rhs.x;
      });
  auto yExtremes = minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(),
      [](const ofPoint &lhs, const ofPoint &rhs) {
        return lhs.y < rhs.y;
      });
  auto zExtremes = minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(),
      [](const ofPoint &lhs, const ofPoint &rhs) {
        return lhs.z < rhs.z;
      });
  ofVec3f boundingBox = ofVec3f(xExtremes.second->x - xExtremes.first->x,
      yExtremes.second->y - yExtremes.first->y,
      zExtremes.second->z - zExtremes.first->z);

  this->initialScaleFactor = DEFAULT_SIZE / max(boundingBox.z, max(boundingBox.x, boundingBox.y));

  this->primitive->setPosition(position);
  this->primitive->setScale(this->initialScaleFactor);
}

void Model3D::updateProperties() {
  SceneObject::updateProperties();
  if (this->properties.at(PROPERTY_ID::SIZE)->isValueChanged()) {
    this->set_size(this->getPropertyValue<float>(PROPERTY_ID::SIZE));
    this->properties.at(PROPERTY_ID::SIZE)->setChanged(false);
  }
}

void Model3D::set_size(const float size) {
  this->primitive.get()->setScale((size / DEFAULT_SIZE) * this->initialScaleFactor);
}
