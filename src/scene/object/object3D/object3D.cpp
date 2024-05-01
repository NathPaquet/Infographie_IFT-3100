#include "object3D.h"

#include "constants.h"
#include "textures/TextureRepository.h"

Object3D::Object3D() {
  this->addProperty<bool>(PROPERTY_ID::SHOW_WIREFRAME, false);
  this->addProperty<ofImage>(PROPERTY_ID::IMAGE_IMPORT, ofImage());
  this->addProperty<const TexturePack *>(PROPERTY_ID::TEXTURE, nullptr);
  this->addProperty<float>(PROPERTY_ID::ANGLE_X, 0.f);
  this->addProperty<float>(PROPERTY_ID::ANGLE_Y, 0.f);
  this->addProperty<float>(PROPERTY_ID::ANGLE_Z, 0.f);

  // Set default color
  this->mMaterial.setDiffuseColor(this->getPropertyValue<ofColor>(PROPERTY_ID::COLOR));
}

void Object3D::draw(bool isSelected, bool isBoundingBoxEnable, bool isObjectAxisEnable) const {
  ofPushStyle();
  if (isSelected) {
    ofSetColor(Constants::SELECTED_OBJECT_FRAME_COLOR);
    primitive->drawWireframe();

    if (isBoundingBoxEnable) {
      this->drawBoundingBox();
    }

    if (isObjectAxisEnable) {
      this->drawAxis();
    }
  }
  ofSetColor(this->getPropertyValue<ofColor>(PROPERTY_ID::COLOR));

  if (!this->getPropertyValue<bool>(PROPERTY_ID::SHOW_WIREFRAME)) {
    if (this->getPropertyValue<const TexturePack *>(PROPERTY_ID::TEXTURE) && this->getPropertyValue<const TexturePack *>(PROPERTY_ID::TEXTURE)->textureDiffuseMap.isAllocated()) {
      this->getPropertyValue<const TexturePack *>(PROPERTY_ID::TEXTURE)->textureDiffuseMap.bind();
      this->getPropertyValue<const TexturePack *>(PROPERTY_ID::TEXTURE)->material.begin();
      primitive->draw();

      this->getPropertyValue<const TexturePack *>(PROPERTY_ID::TEXTURE)->material.end();
      this->getPropertyValue<const TexturePack *>(PROPERTY_ID::TEXTURE)->textureDiffuseMap.unbind();
    } else {
      mMaterial.begin();
      primitive->draw();
      mMaterial.end();
    }

  } else {
    ofNoFill();
    // primitive->draw();
    primitive->drawWireframe();
  }
  ofPopStyle();
}

void Object3D::drawAxis() const {
  ofVec3f xAxis = this->primitive->getXAxis();
  ofVec3f yAxis = this->primitive->getYAxis();
  ofVec3f zAxis = this->primitive->getZAxis();

  auto vecScale = this->primitive->getScale();
  auto vecRescale = vecScale * (1.25f * Constants::DEFAULT_SIZE);
  float scaleHeadArrow = vecRescale.x / 8;
  ofPushStyle();
  ofPushMatrix();

  ofTranslate(this->position);
  ofSetColor(ofColor::red);
  ofDrawArrow(ofPoint(0), ofPoint(xAxis * vecRescale.x), scaleHeadArrow);

  ofSetColor(ofColor::green);
  ofDrawArrow(ofPoint(0), ofPoint(yAxis * vecRescale.y), scaleHeadArrow);

  ofSetColor(ofColor::blue);
  ofDrawArrow(ofPoint(0), ofPoint(zAxis * vecRescale.z), scaleHeadArrow);

  ofPopMatrix();
  ofPopStyle();
}

void Object3D::drawBoundingBox() const {
  ofPushStyle();
  ofNoFill();
  ofSetColor(ofColor::yellow);

  this->drawAABB();

  ofPopStyle();
}

void Object3D::drawAABB() const {
  vector<glm::vec3> vertices = this->primitive->getMesh().getVertices();
  if (vertices.empty()) {
    return;
  }

  ofQuaternion rotation = primitive->getOrientationQuat();
  ofVec3f scale = primitive->getScale();

  for (auto &vertex : vertices) {
    vertex *= scale;
    vertex = rotation * vertex;
  }

  ofVec3f minBound(vertices[0]), maxBound(vertices[0]);
  for (const auto &vertex : vertices) {
    minBound.x = min(minBound.x, vertex.x);
    minBound.y = min(minBound.y, vertex.y);
    minBound.z = min(minBound.z, vertex.z);

    maxBound.x = max(maxBound.x, vertex.x);
    maxBound.y = max(maxBound.y, vertex.y);
    maxBound.z = max(maxBound.z, vertex.z);
  }

  ofVec3f center = ofVec3f(
      (maxBound.x + minBound.x) / 2,
      (maxBound.y + minBound.y) / 2,
      (maxBound.z + minBound.z) / 2);

  center += this->primitive->getGlobalPosition();

  ofVec3f boundingBoxDimensions = maxBound - minBound;

  ofDrawBox(center.x, center.y, center.z, boundingBoxDimensions.x, boundingBoxDimensions.y, boundingBoxDimensions.z);
}

void Object3D::updateProperties() {
  SceneObject::updateProperties();
  if (this->properties.at(PROPERTY_ID::IMAGE_IMPORT)->isValueChanged() && this->getPropertyValue<ofImage>(PROPERTY_ID::IMAGE_IMPORT).isAllocated()) {
    this->properties.at(PROPERTY_ID::IMAGE_IMPORT)->setChanged(false);
  }
  if (this->properties.at(PROPERTY_ID::IMAGE_IMPORT)->isValueChanged()) {
    this->properties.at(PROPERTY_ID::IMAGE_IMPORT)->setChanged(false);
  }
  if (this->properties.at(PROPERTY_ID::ANGLE_X)->isValueChanged() || this->properties.at(PROPERTY_ID::ANGLE_Y)->isValueChanged() || this->properties.at(PROPERTY_ID::ANGLE_Z)->isValueChanged()) {
    this->primitive->setOrientation({this->getPropertyValue<float>(PROPERTY_ID::ANGLE_X), this->getPropertyValue<float>(PROPERTY_ID::ANGLE_Y), this->getPropertyValue<float>(PROPERTY_ID::ANGLE_Z)});
    this->properties.at(PROPERTY_ID::ANGLE_X)->setChanged(false);
    this->properties.at(PROPERTY_ID::ANGLE_Y)->setChanged(false);
    this->properties.at(PROPERTY_ID::ANGLE_Z)->setChanged(false);
  }
  if (this->properties.at(PROPERTY_ID::COLOR)->isValueChanged()) {
    this->mMaterial.setDiffuseColor(this->getPropertyValue<ofColor>(PROPERTY_ID::COLOR));
    this->properties.at(PROPERTY_ID::COLOR)->setChanged(false);
  }
}