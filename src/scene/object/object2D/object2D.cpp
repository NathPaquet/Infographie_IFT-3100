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
  ofVec3f xAxis = this->primitive->getXAxis();
  ofVec3f yAxis = this->primitive->getYAxis();

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

  ofPopMatrix();
  ofPopStyle();
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
