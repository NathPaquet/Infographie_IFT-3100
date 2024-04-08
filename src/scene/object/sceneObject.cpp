#include "sceneObject.h"

#include "ImageImporter.h"
#include "constants.h"

SceneObject::SceneObject() {
  this->addProperty<ofColor>(PROPERTY_ID::COLOR, ofColor::fromHsb(ofRandom(255), 255, 255));
  this->addProperty<bool>(PROPERTY_ID::SHOW_WIREFRAME, false);
}

std::map<PROPERTY_ID, std::unique_ptr<PropertyBase>> &SceneObject::getProperties() {
  return this->properties;
}

void SceneObject::updateProperties() {
}

const of3dPrimitive &SceneObject::getPrimitive() const {
  return *this->primitive;
}

const ofVec3f &SceneObject::getPosition() const {
  return this->position;
}

void SceneObject::setPosition(ofVec3f vec) {
  this->position = vec;
  this->primitive->setGlobalPosition(vec);
}

void SceneObject::setDraggingPosition(ofVec3f vec) {
  this->draggingPosition = vec;
}
