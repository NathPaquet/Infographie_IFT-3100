#include "Object2D.h"

#include "Constants.h"

Object2D::Object2D() {
  this->addProperty<float>(PROPERTY_ID::ANGLE_Z, 0.f);
}

void Object2D::draw(bool isSelected, bool isBoundingBoxEnable, bool isObjectAxisEnable) {
  this->updateProperties();
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
    primitive->draw();
  } else {
    ofNoFill();
    // primitive->draw();
    primitive->drawWireframe();
  }
  ofPopStyle();
}

void Object2D::drawAxis() {
}

void Object2D::drawBoundingBox() {
}

void Object2D::updateProperties() {
  SceneObject::updateProperties();
  if (this->properties.at(PROPERTY_ID::ANGLE_Z)->isValueChanged()) {
    this->primitive->setOrientation({0, 0, this->getPropertyValue<float>(PROPERTY_ID::ANGLE_Z)});
    this->properties.at(PROPERTY_ID::ANGLE_Z)->setChanged(false);
  }
}
