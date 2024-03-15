#include "scene2DEventHandler.h"

Scene2DEventHandler::~Scene2DEventHandler() {
  if (this->isActivated) {
    this->deactivateHandler();
  }
}

void Scene2DEventHandler::activateHandler() {
  this->isActivated = true;

  ofAddListener(ofEvents().mouseDragged, this, &Scene2DEventHandler::mouseDragged);
  ofAddListener(ofEvents().mousePressed, this, &Scene2DEventHandler::mousePressed);
  ofAddListener(ofEvents().mouseReleased, this, &Scene2DEventHandler::mouseReleased);
  // TODO : Call scene2D to active only movement in 2D scene (movement in x and y)
}

void Scene2DEventHandler::deactivateHandler() {
  this->isActivated = false;

  ofRemoveListener(ofEvents().mouseDragged, this, &Scene2DEventHandler::mouseDragged);
  ofRemoveListener(ofEvents().mousePressed, this, &Scene2DEventHandler::mousePressed);
  ofRemoveListener(ofEvents().mouseReleased, this, &Scene2DEventHandler::mouseReleased);
  // TODO : Call scene2D to deactive only movement in 2D scene (movement in x and y)
}

bool Scene2DEventHandler::isMouseInScene() const {
  return !ImGui::GetIO().WantCaptureMouse;
}

void Scene2DEventHandler::mouseDragged(ofMouseEventArgs &mouseArgs) {
  if (this->isMouseInScene()) {
    switch (this->cursor->getCursorMode()) {
      case CursorMode::GRABBING:
        this->scene2D->dragObjectWithMouse();
        break;
      case CursorMode::CAMERA_MOVING:
        this->scene2D->moveCameraWithMouse();
        break;
      default:
        break;
    }
  }
}

void Scene2DEventHandler::mousePressed(ofMouseEventArgs &mouseArgs) {
  if (this->isMouseInScene()) {
    if (mouseArgs.button == OF_MOUSE_BUTTON_LEFT) {
      this->leftMouseButtonPressed();
    }
  }
}

void Scene2DEventHandler::mouseReleased(ofMouseEventArgs &mouseArgs) {
  if (this->isMouseInScene()) {
    if (mouseArgs.button == OF_MOUSE_BUTTON_LEFT) {
      this->leftMouseButtonReleased();
    }
  }
}

void Scene2DEventHandler::leftMouseButtonPressed() {
  switch (this->cursor->getCursorMode()) {
    case CursorMode::NAVIGATION:
      if (this->scene2D->attemptToClickOnObjectWithMouse()) {
        this->cursor->setCursorMode(CursorMode::GRABBING);
      } else {
        this->cursor->setCursorMode(CursorMode::CAMERA_MOVING);
      }
      break;
    case CursorMode::ADDING:
      if (this->scene2D->attemptToAddObjectWithMouse()) {
        this->cursor->setCursorMode(CursorMode::NAVIGATION);
      }
      break;
    case CursorMode::REMOVING:
      if (this->scene2D->attemptToRemoveObjectWihMouse()) {
        this->cursor->setCursorMode(CursorMode::NAVIGATION);
      }
      break;
    default:
      break;
  }
}

void Scene2DEventHandler::leftMouseButtonReleased() {
  switch (this->cursor->getCursorMode()) {
    case CursorMode::GRABBING:
      this->scene2D->releaseDraggedObject();
      this->cursor->setCursorMode(CursorMode::NAVIGATION);
      break;
    case CursorMode::CAMERA_MOVING:
      this->cursor->setCursorMode(CursorMode::NAVIGATION);
      break;
    default:
      break;
  }
}
