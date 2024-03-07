#include "scene2D.h"

#include "constants.h"

void Scene2D::setup() {
  // this->camera.setDistance(Constants::DEFAULT_CAMERA_DISTANCE);
  this->ray = Ray();
  this->camera.removeAllInteractions();
  this->camera.disableMouseMiddleButton();
  this->camera.disableMouseInput();

  this->camera.addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_XY, OF_MOUSE_BUTTON_LEFT);
  this->camera.addInteraction(ofEasyCam::TRANSFORM_NONE, OF_MOUSE_BUTTON_MIDDLE);

  ofDisableLighting();
}

void Scene2D::drawScene() {
  ofPushStyle();
  // ofBackground(this->backgroundColor);
  this->cursor->drawCursor(ofGetMouseX(), ofGetMouseY());
  this->camera.begin();
  this->processMouseActions();
  this->sceneManager->drawScene();
  this->camera.begin();
  ofPopStyle();
}

void Scene2D::processMouseActions() {
  if (!isMouseClickInScene()) {
    return;
  }

  if (!isMouseClickInScene()) {
    return;
  }
  auto &&maybeObject = this->cursor->setRayWithCollidingObject(this->sceneManager->getObjects(), this->camera, this->ray);
  auto &&found = maybeObject.has_value();
  const float distance = Constants::DEFAULT_DISTANCE_TO_DRAW_PRIMITIVE;
  auto position = (this->ray.getOrigin() + this->ray.getDirection() * (distance / abs(ray.getDirection().z)));
  // this->ray.set(this->camera.getPosition(), this->camera.getZAxis());
  if (this->wasDrawingFirstPositionClicked && this->cursor->getCursorMode() == CursorMode::ADDING) {
    this->ray.drawPrimitivePreview(this->currentObjectToAdd, this->drawingFirstPosition, position);
  }
  /*
  if (found && std::find(this->sceneManager.get()->getSelectedObjects().begin(), this->sceneManager.get()->getSelectedObjects().end(), maybeObject.value()) != this->sceneManager.get()->getSelectedObjects().end()) {
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
      shouldDragObject = true;
    }

    if (ImGui::IsMouseDown(ImGuiMouseButton_Left)
        && shouldDragObject
        && this->cursor->getCursorMode() == CursorMode::NAVIGATION) {
      this->sceneManager.get()->setObjectPosition(maybeObject.value(), ray.getOrigin() + ray.getDirection() * distance);
      this->camera.disableMouseInput();
    }
  }

  */
  if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
    if (this->cursor->getCursorMode() == CursorMode::ADDING) {
      if (this->wasDrawingFirstPositionClicked) {
        this->sceneManager->addElement(this->drawingFirstPosition, position, this->currentObjectToAdd);
        this->cursor->setCursorMode(CursorMode::NAVIGATION);
        this->sceneManager->setSelectedSceneObject(this->sceneManager->getObjects().back().get());
      } else {
        this->drawingFirstPosition = position;
      }
      this->wasDrawingFirstPositionClicked = !this->wasDrawingFirstPositionClicked;
    }
    if (found && this->cursor->getCursorMode() == CursorMode::NAVIGATION) {
      if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftCtrl))) {
        this->sceneManager->clickSelectionSceneObject(maybeObject.value());
      } else {
        this->sceneManager->setSelectedSceneObject(maybeObject.value());
      }

    } else if (found && this->cursor->getCursorMode() == CursorMode::REMOVING) {
      this->sceneManager->removeObject(maybeObject.value()); // TODO : Ajouter une nouvelle m�thode pour supprimer un objet
      this->cursor->setCursorMode(CursorMode::NAVIGATION);
    }
  }
}
