#include "scene3DEventHandler.h"

Scene3DEventHandler::~Scene3DEventHandler() {
  if (this->isActivated) {
    this->deactivateHandler();
  }
}

void Scene3DEventHandler::activateHandler() {
  this->isActivated = true;

  ofAddListener(ofEvents().mouseMoved, this, &Scene3DEventHandler::mouseMoved);
}

void Scene3DEventHandler::deactivateHandler() {
  this->isActivated = false;

  ofRemoveListener(ofEvents().mouseMoved, this, &Scene3DEventHandler::mouseMoved);
}

bool Scene3DEventHandler::isMouseClickInScene() const {
  return !ImGui::GetIO().WantCaptureMouse;
}

void Scene3DEventHandler::mouseMoved(ofMouseEventArgs &mouseArgs) {
  if (this->isMouseClickInScene()) {
    ofLogNotice("Scene3DEventHandler") << "Mouse moved";
  }
}
