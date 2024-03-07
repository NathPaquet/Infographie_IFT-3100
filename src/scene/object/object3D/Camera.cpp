#include "Camera.h"

Camera::Camera(ofVec3f position) {
  auto sphere = ofSpherePrimitive(CAMERA_RADIUS, 20, OF_PRIMITIVE_TRIANGLES);

  this->primitive = std::make_unique<ofSpherePrimitive>(sphere);
  this->primitive->setPosition(position);

  this->camera = std::make_unique<ofEasyCam>();
}

void Camera::updateProperties() {
  SceneObject::updateProperties();

  auto cameraViewAxis = -this->primitive.get()->getZAxis();

  getCamera()->setPosition(this->primitive.get()->getPosition());
  getCamera()->setOrientation(this->primitive.get()->getOrientationQuat());

  ofPushMatrix();
  ofPushStyle();

  ofTranslate(this->primitive.get()->getPosition());
  ofSetColor(ofColor::white);
  ofDrawLine(ofPoint(0), ofPoint(cameraViewAxis * CAMERA_LINE_LENGTH));

  ofPopStyle();
  ofPopMatrix();
}

ofCamera *Camera::getCamera() {
  return camera.get();
}
