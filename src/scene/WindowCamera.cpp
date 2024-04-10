#include "WindowCamera.h"

#include "Constants.h"

WindowCamera::WindowCamera(Scene3D *scene):
    scene(scene) {}

void WindowCamera::setSelectedCamera(Camera *camera) {
  this->selectedCamera = camera;
}

Camera *WindowCamera::getSelectedCamera() const {
  return this->selectedCamera;
}

bool WindowCamera::getIsShow() const {
  return this->isShown;
}

void WindowCamera::drawScene() {
  if (!isShown || hasNoSelectedCamera()) {
    return;
  }

  const float SCENE_WIDTH = ofGetWidth() - Constants::SCENE_GRAPH_WIDTH - Constants::PROPERTIES_PANEL_WIDTH;
  const float WINDOW_WIDTH = SCENE_WIDTH * RATIO_SCENE;
  const float WINDOW_HEIGHT = ofGetHeight() * RATIO_SCENE;

  ofRectangle viewport = ofRectangle(
      Constants::SCENE_GRAPH_WIDTH, ofGetHeight() - WINDOW_HEIGHT,
      WINDOW_WIDTH, WINDOW_HEIGHT);

  ofDisableDepthTest();
  ofPushStyle();

  ofSetColor(ofColor::black);
  ofDrawRectangle(viewport);

  ofPopStyle();
  ofEnableDepthTest();

  selectedCamera->getCamera()->begin(viewport);
  scene->drawSceneFromCamera(selectedCamera->getCamera()->getGlobalPosition());
  selectedCamera->getCamera()->end();
}

void WindowCamera::switchIsShown() {
  isShown = !isShown;
}

bool WindowCamera::hasNoSelectedCamera() const {
  return selectedCamera == nullptr;
}
