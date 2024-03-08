#include "WindowCamera.h"

#include "Constants.h"

WindowCamera::WindowCamera(SceneManager *sceneManager):
    sceneManager(sceneManager) {}

void WindowCamera::setSelectedCamera(Camera *camera) {
  this->selectedCamera = camera;
}

void WindowCamera::drawScene() {
  if (!isShown || !hasASelectedCamera()) {
    return;
  }

  const float SCENE_WIDTH = ofGetWidth() - Constants::SCENE_GRAPH_WIDTH - Constants::PROPERTIES_PANEL_WIDTH;
  const float WINDOW_WIDTH = SCENE_WIDTH * 0.375f;
  const float WINDOW_HEIGHT = ofGetHeight() * 0.375f;

  ofRectangle viewport = ofRectangle(
      Constants::SCENE_GRAPH_WIDTH, ofGetHeight() - WINDOW_HEIGHT,
      WINDOW_WIDTH, WINDOW_HEIGHT);

  ofPushMatrix();
  ofPushStyle();

  ofSetColor(0);
  ofSetLineWidth(3);
  ofNoFill();

  ofDrawRectangle(viewport);

  ofPopStyle();
  ofPopMatrix();

  selectedCamera->getCamera()->begin(viewport);
  sceneManager->drawScene();
  selectedCamera->getCamera()->end();
}

void WindowCamera::switchIsShown() {
  isShown = !isShown;
}

void WindowCamera::setIsShown(bool isShown) {
  this->isShown = isShown;
}

bool WindowCamera::hasASelectedCamera() const {
  return selectedCamera != nullptr;
}
