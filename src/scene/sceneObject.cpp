#include "sceneObject.h"

void SceneObject::draw() const {
  ofPushStyle();
  if (mTex.isAllocated()) {
    mTex.bind();
    primitive->draw();
    mTex.unbind();
  } else {
    ofSetColor(colorPicker.getNormalizedColor());
    primitive->draw();
  }
  ofPopStyle();
}

void SceneObject::draw_properties() {
}

const of3dPrimitive &SceneObject::getPrimitive() const {
  return *this->primitive.get();
}
