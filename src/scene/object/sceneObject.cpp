#include "sceneObject.h"

#include "ImageImporter.h"
#include "constants.h"

SceneObject::SceneObject() {
  this->addProperty<ofImage>(PROPERTY_ID::IMAGE_IMPORT, ofImage());
  this->addProperty<ofColor>(PROPERTY_ID::COLOR, ofColor::fromHsb(ofRandom(255), 255, 255));
  this->addProperty<ofVec3f>(PROPERTY_ID::ANGLES, ofVec3f(0.f, 0.f, 0.f));
  this->addProperty<bool>(PROPERTY_ID::SHOW_WIREFRAME, false);
}

void SceneObject::draw(bool isSelected, bool isBoundingBoxEnable) {
  this->updateProperties();
  ofPushStyle();
  if (isSelected) {
    drawAxis();
    ofSetColor(Constants::SELECTED_OBJECT_FRAME_COLOR);
    primitive->drawWireframe();

    if (isBoundingBoxEnable) {
      this->drawBoundingBox();
    }
  }
  ofSetColor(this->getPropertyValue<ofColor>(PROPERTY_ID::COLOR));

  if (!this->getPropertyValue<bool>(PROPERTY_ID::SHOW_WIREFRAME)) {
  if (mTex.isAllocated()) {
    this->mTex.bind();
    // mMaterial.setDiffuseColor(this->getPropertyValue<ofColor>(PROPERTY_ID::COLOR));
    // mMaterial.begin();
    primitive->draw();
    // mMaterial.end();
    this->mTex.unbind();
  } else {
    // mMaterial.setDiffuseColor(this->getPropertyValue<ofColor>(PROPERTY_ID::COLOR));
    // mMaterial.begin();
    primitive->draw();
    // mMaterial.end();
  } else {
    ofNoFill();
    // primitive->draw();
    primitive->drawWireframe();
  }
  ofPopStyle();
}

void SceneObject::draw_properties() {
}

std::map<PROPERTY_ID, std::unique_ptr<PropertyBase>> &SceneObject::getProperties() {
  // TODO : we shouldn't make a copy here
  return this->properties;
}

void SceneObject::drawAxis() {
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

void SceneObject::drawCustomWireFrame(const float lineThickness) {
  ofMesh &mesh = this->primitive->getMesh();
  auto mode = mesh.getMode();
  mesh.setMode(OF_PRIMITIVE_LINES);
  for (int i = 0; i < mesh.getNumVertices(); i += 2) {
    ofVec3f v1 = mesh.getVertex(i);
    ofVec3f v2 = mesh.getVertex(i + 1);
    ofVec3f direction = (v2 - v1).getNormalized();
    ofVec3f normal = direction.getCrossed(ofVec3f(0, 0, 1)).getNormalized(); // Cross product with Z-axis

    ofVec3f offset = normal * lineThickness / 2.0;

    ofBeginShape();
    ofVertex(v1 + offset);
    ofVertex(v2 + offset);
    ofEndShape();

    ofBeginShape();
    ofVertex(v1 - offset);
    ofVertex(v2 - offset);
    ofEndShape();
  }
  mesh.setMode(mode);
}

void SceneObject::updateProperties() {
  if (this->properties.at(PROPERTY_ID::IMAGE_IMPORT)->isValueChanged() && this->getPropertyValue<ofImage>(PROPERTY_ID::IMAGE_IMPORT).isAllocated()) {
    this->mTex = this->getPropertyValue<ofImage>(PROPERTY_ID::IMAGE_IMPORT).getTexture();
    this->mTex.enableMipmap();
    this->mTex.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    this->mTex.generateMipmap();
    this->properties.at(PROPERTY_ID::IMAGE_IMPORT)->setChanged(false);
  }
  if (this->properties.at(PROPERTY_ID::IMAGE_IMPORT)->isValueChanged()) {
    this->mTex.clear();
    this->properties.at(PROPERTY_ID::IMAGE_IMPORT)->setChanged(false);
  }
  if (this->properties.at(PROPERTY_ID::ANGLES)->isValueChanged()) {
    this->primitive.get()->setOrientation(this->getPropertyValue<ofVec3f>(PROPERTY_ID::ANGLES));
    this->properties.at(PROPERTY_ID::ANGLES)->setChanged(false);
  }
}

void SceneObject::drawBoundingBox() {
  ofPushStyle();
  ofNoFill();
  ofSetColor(ofColor::yellow);

  this->drawAABB();

  ofPopStyle();
}

void SceneObject::drawAABB() const {
  vector<glm::vec3> vertices = this->primitive.get()->getMesh().getVertices();
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

  center += this->primitive.get()->getGlobalPosition();

  ofVec3f boundingBoxDimensions = maxBound - minBound;

  ofDrawBox(center.x, center.y, center.z, boundingBoxDimensions.x, boundingBoxDimensions.y, boundingBoxDimensions.z);
}

const of3dPrimitive &SceneObject::getPrimitive() const {
  return *this->primitive;
}

void SceneObject::setPosition(ofVec3f vec) {
  this->position = vec;
  this->primitive->setGlobalPosition(vec);
}
