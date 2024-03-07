#include "WindowCamera.h"

WindowCamera::WindowCamera(SceneManager *sceneManager):
    sceneManager(sceneManager) {}

void WindowCamera::setSelectedCamera(Camera *camera) {
  this->selectedCamera = camera;
}

void WindowCamera::drawScene() {
  if (!isShown || !hasASelectedCamera()) {
    return;
  }

  ofPushMatrix();
  ofPushStyle();

  ofTranslate(0, ofGetHeight());
  ofScale(1, -1);

  ofSetColor(0);
  ofNoFill();
  // Constants::SCENE_GRAPH_WIDTH / 2
  ofDrawRectangle(0, 0, ofGetWidth() / 2, ofGetHeight() / 2);

  ofPopStyle();
  ofPopMatrix();

  ofRectangle viewport = ofRectangle(0, ofGetHeight() / 2, ofGetWidth() / 2, ofGetHeight() / 2);

  selectedCamera->getCamera()->begin(viewport);
  sceneManager->drawScene();
  selectedCamera->getCamera()->end();
}

void WindowCamera::setIsShown(bool isShown) {
  this->isShown = isShown;
}

bool WindowCamera::hasASelectedCamera() const {
  return selectedCamera != nullptr;
}
