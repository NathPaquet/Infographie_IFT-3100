#include "Model3D.h"

#include "constants.h"

#include <ofxAssimpModelLoader.h>

Model3D::Model3D(const glm::vec3 &position, const string &modelPath) {
  this->addProperty<float>(PROPERTY_ID::SIZE, Constants::DEFAULT_SIZE);
  // TODO : find a way not to load mesh in this section !

  ofxAssimpModelLoader model;
  model.load(modelPath, ofxAssimpModelLoader::OPTIMIZE_DEFAULT);
  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(model.getMesh(0)));

  model.setScaleNormalization(false);
  ofMesh mesh = model.getMesh(0);
  ofVec3f boundingBox = this->getBoundingBoxDimensions(mesh);

  this->initialScaleFactor = Constants::DEFAULT_SIZE / max(boundingBox.z, max(boundingBox.x, boundingBox.y));

  this->primitive->setPosition(position);
  this->primitive->setScale(this->initialScaleFactor);
}

void Model3D::updateProperties() {
  Object3D::updateProperties();
  if (this->properties.at(PROPERTY_ID::SIZE)->isValueChanged()) {
    this->set_size(this->getPropertyValue<float>(PROPERTY_ID::SIZE));
    this->properties.at(PROPERTY_ID::SIZE)->setChanged(false);
  }
}

void Model3D::set_size(const float size) {
  this->primitive.get()->setScale((size / Constants::DEFAULT_SIZE) * this->initialScaleFactor);
}

ofVec3f Model3D::getBoundingBoxDimensions(const ofMesh &mesh) const {
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
  return ofVec3f(xExtremes.second->x - xExtremes.first->x,
      yExtremes.second->y - yExtremes.first->y,
      zExtremes.second->z - zExtremes.first->z);
}

void Model3D::drawAxis() {
  ofVec3f xAxis = this->primitive.get()->getXAxis();
  ofVec3f yAxis = this->primitive.get()->getYAxis();
  ofVec3f zAxis = this->primitive.get()->getZAxis();

  ofVec3f arrowLength = (this->getBoundingBoxDimensions(this->primitive->getMesh()) * this->primitive.get()->getScale()) * 0.65;
  float scaleHeadArrow = this->getPropertyValue<float>(PROPERTY_ID::SIZE) / Constants::DEFAULT_SIZE;

  ofPushMatrix();

  ofTranslate(this->primitive.get()->getGlobalPosition());
  ofSetColor(ofColor::red);
  ofDrawArrow(ofPoint(0), ofPoint(xAxis * arrowLength.x), scaleHeadArrow);

  ofSetColor(ofColor::green);
  ofDrawArrow(ofPoint(0), ofPoint(yAxis * arrowLength.y), scaleHeadArrow);

  ofSetColor(ofColor::blue);
  ofDrawArrow(ofPoint(0), ofPoint(zAxis * arrowLength.z), scaleHeadArrow);

  ofPopMatrix();
}
