#include "scene3DEventHandler.h"

Scene3DEventHandler::~Scene3DEventHandler() {
  if (this->isActivated) {
    this->deactivateHandler();
  }
}

void Scene3DEventHandler::activateHandler() {
  this->isActivated = true;

  ofAddListener(ofEvents().mouseMoved, this, &Scene3DEventHandler::mouseMoved);
  ofAddListener(ofEvents().mouseDragged, this, &Scene3DEventHandler::mouseDragged);
  ofAddListener(ofEvents().mousePressed, this, &Scene3DEventHandler::mousePressed);
  ofAddListener(ofEvents().mouseReleased, this, &Scene3DEventHandler::mouseReleased);
  ofAddListener(ofEvents().mouseScrolled, this, &Scene3DEventHandler::mousePressedAndScrolled);
  this->scene3D->activateCameraMouseInput();
}

void Scene3DEventHandler::deactivateHandler() {
  this->isActivated = false;

  ofRemoveListener(ofEvents().mouseMoved, this, &Scene3DEventHandler::mouseMoved);
  ofRemoveListener(ofEvents().mouseDragged, this, &Scene3DEventHandler::mouseDragged);
  ofRemoveListener(ofEvents().mousePressed, this, &Scene3DEventHandler::mousePressed);
  ofRemoveListener(ofEvents().mouseReleased, this, &Scene3DEventHandler::mouseReleased);
  ofRemoveListener(ofEvents().mouseScrolled, this, &Scene3DEventHandler::mousePressedAndScrolled);
  this->scene3D->deactivateCameraMouseInput();
}

bool Scene3DEventHandler::isMouseInScene() const {
  return !ImGui::GetIO().WantCaptureMouse;
}

void Scene3DEventHandler::mouseMoved(ofMouseEventArgs &mouseArgs) {
  if (this->isMouseInScene()) {
    if (this->cursor->getCursorMode() == CursorMode::NAVIGATION) {
      this->scene3D->activateCameraMouseInput();
    }
  } else {
    this->scene3D->deactivateCameraMouseInput();
  }
}

void Scene3DEventHandler::mouseDragged(ofMouseEventArgs &mouseArgs) {
  if (this->isMouseInScene()) {
    if (this->cursor->getCursorMode() == CursorMode::GRABBING) {
      this->scene3D->deactivateCameraMouseInput();
      this->scene3D->dragObjectWithMouse();
    }
  }
}

void Scene3DEventHandler::mousePressed(ofMouseEventArgs &mouseArgs) {
  if (this->isMouseInScene()) {
    if (mouseArgs.button == OF_MOUSE_BUTTON_LEFT) {
      this->leftMouseButtonPressed();
    }
  }
}

void Scene3DEventHandler::mouseReleased(ofMouseEventArgs &mouseArgs) {
  if (this->isMouseInScene()) {
    if (mouseArgs.button == OF_MOUSE_BUTTON_LEFT) {
      this->leftMouseButtonReleased();
    }
  }
}

void Scene3DEventHandler::mousePressedAndScrolled(ofMouseEventArgs &mouseArgs) {
  if (this->isMouseInScene() && mouseArgs.button == OF_MOUSE_BUTTON_LEFT) {
    this->scene3D->moveObjectWithScrollOnly(mouseArgs.scrollY);
  }
}

void Scene3DEventHandler::leftMouseButtonPressed() {
  switch (this->cursor->getCursorMode()) {
    case CursorMode::NAVIGATION:
      if (this->scene3D->attemptToClickOnObjectWithMouse()) {
        this->cursor->setCursorMode(CursorMode::GRABBING);
      } else {
        this->cursor->setCursorMode(CursorMode::CAMERA_MOVING);
      }
      break;
    case CursorMode::ADDING:
      if (this->scene3D->attemptToAddObjectWithMouse()) {
        this->cursor->setCursorMode(CursorMode::NAVIGATION);
      }
      break;
    case CursorMode::REMOVING:
      if (this->scene3D->attemptToRemoveObjectWihMouse()) {
        this->cursor->setCursorMode(CursorMode::NAVIGATION);
      }
      break;
    default:
      break;
  }
}

void Scene3DEventHandler::leftMouseButtonReleased() {
  switch (this->cursor->getCursorMode()) {
    case CursorMode::GRABBING:
      this->scene3D->releaseDraggedObject();
      this->scene3D->activateCameraMouseInput();
      this->cursor->setCursorMode(CursorMode::NAVIGATION);
      break;
    case CursorMode::CAMERA_MOVING:
      this->cursor->setCursorMode(CursorMode::NAVIGATION);
      break;
    default:
      break;
  }
}
