#include "WindowCamera.h"

WindowCamera::WindowCamera(SceneManager *sceneManager):
    sceneManager(sceneManager) {}

void WindowCamera::setSelectedCamera(Camera *camera) {
  this->selectedCamera = camera;
}

void WindowCamera::draw() {
  if (!isShown) {
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

  ofViewport(0, 0, ofGetWidth() / 2, ofGetHeight() / 2); // Pourquoi change pas avec translate ?

  ofPopStyle();
  ofPopMatrix();

  selectedCamera->getCamera()->disableMouseInput();

  selectedCamera->getCamera()->begin();
  sceneManager->drawScene();
  selectedCamera->getCamera()->end();
}

void WindowCamera::setIsShown(bool isShown) {
  this->isShown = isShown && selectedCamera != nullptr;
}
