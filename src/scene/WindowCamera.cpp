#include "WindowCamera.h"

#include "SceneManager.h"

WindowCamera::WindowCamera(SceneManager *sceneManager):
    sceneManager(sceneManager) {}

void WindowCamera::draw() {
  // selectedCamera = std::make_unique<Camera>(sceneManager->getSelectedObjects().at(0));

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

  ofViewport(0, 0, ofGetWidth() / 2, ofGetHeight() / 2);

  ofPopStyle();
  ofPopMatrix();

  selectedCamera.get()->getCamera()->disableMouseInput();

  selectedCamera.get()->getCamera()->begin();
  sceneManager->drawScene();
  selectedCamera.get()->getCamera()->end();
}

void WindowCamera::setIsShown(bool isShown) {
  this->isShown = isShown && selectedCamera != nullptr;
}
