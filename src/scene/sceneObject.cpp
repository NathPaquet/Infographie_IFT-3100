#include "sceneObject.h"

#include "ImageImporter.h"

SceneObject::SceneObject() {
  this->addProperty<ofImage>(PROPERTY_ID::IMAGE_IMPORT, ofImage());
  this->addProperty<ofColor>(PROPERTY_ID::COLOR, ofColor::fromHsb(ofRandom(255), 255, 255));
  this->addProperty<ofVec3f>(PROPERTY_ID::ANGLES, ofVec3f(0.f, 0.f, 0.f));
}

void SceneObject::draw(bool isSelected) {
  this->updateProperties();
  ofPushStyle();
  if (isSelected) {
    ofColor complementaryColor(255 - this->color.r, 255 - this->color.g, 255 - this->color.b);
    ofSetColor(complementaryColor);
    primitive->drawWireframe();
  }

  if (mTex.isAllocated()) {
    this->mTex.bind();
    ofSetColor(this->getPropertyValue<ofColor>(PROPERTY_ID::COLOR));
    primitive->draw();
    this->mTex.unbind();
  } else {
    ofSetColor(this->getPropertyValue<ofColor>(PROPERTY_ID::COLOR));
    primitive->draw();
  }
  ofPopStyle();
}

void SceneObject::draw_properties() {
}

std::map<PROPERTY_ID, std::unique_ptr<PropertyBase>> &SceneObject::getProperties() {
  // TODO : we shouldn't make a copy here
  return this->properties;
}

void SceneObject::updateProperties() {
  if (this->properties.at(PROPERTY_ID::IMAGE_IMPORT)->isValueChanged() && this->getPropertyValue<ofImage>(PROPERTY_ID::IMAGE_IMPORT).isAllocated()) {
    this->mTex = this->getPropertyValue<ofImage>(PROPERTY_ID::IMAGE_IMPORT).getTexture();
    this->mTex.enableMipmap();
    this->mTex.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    this->mTex.generateMipmap();
    this->properties.at(PROPERTY_ID::IMAGE_IMPORT)->setChanged(false);
  } else if (this->properties.at(PROPERTY_ID::IMAGE_IMPORT)->isValueChanged()) {
    this->mTex.clear();
    this->properties.at(PROPERTY_ID::IMAGE_IMPORT)->setChanged(false);
  } else if (this->properties.at(PROPERTY_ID::ANGLES)->isValueChanged()) {
    auto angles = this->getPropertyValue<ofVec3f>(PROPERTY_ID::ANGLES);
    this->primitive.get()->setOrientation(angles);
  }
}

const of3dPrimitive &SceneObject::getPrimitive() const {
  return *this->primitive;
}

void SceneObject::setPosition(ofVec3f vec) {
  this->position = vec;
  this->primitive->setGlobalPosition(vec);
}
