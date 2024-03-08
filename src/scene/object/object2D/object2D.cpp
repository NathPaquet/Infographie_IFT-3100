#include "Object2D.h"

#include "Constants.h"

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
    if (mTex.isAllocated()) {
      this->mTex.bind();
      primitive->draw();
      this->mTex.unbind();
    } else {
      primitive->draw();
    }

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
