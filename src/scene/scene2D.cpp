#include "scene2D.h"

#include "constants.h"

void Scene2D::setup() {
  //this->camera.setDistance(Constants::DEFAULT_CAMERA_DISTANCE);
  this->ray = Ray();
  this->camera.disableMouseInput();
  ofDisableLighting();
}

void Scene2D::drawScene() {
  ofPushStyle();
  //ofBackground(this->backgroundColor);
  this->cursor->drawCursor(ofGetMouseX(), ofGetMouseY());
  this->camera.begin();
  this->processMouseActions();
  this->sceneManager.get()->drawScene();
  this->camera.begin();
  ofPopStyle();
}

void Scene2D::processMouseActions() {
  if (!isMouseClickInScene()) {
    return;
  }
  auto &&maybeObject = this->cursor->setRayWithCollidingObject(this->sceneManager.get()->getObjects(), this->camera, this->ray);
  auto &&found = maybeObject.has_value();
  const float distance = Constants::DEFAULT_DISTANCE_TO_DRAW_PRIMITIVE;
  auto position = (this->ray.getOrigin() + this->ray.getDirection() * (distance / abs(ray.getDirection().z)));
  //this->ray.set(this->camera.getPosition(), this->camera.getZAxis());
  if (!found && this->cursor->getCursorMode() == CursorMode::ADDING) {
    this->ray.drawPrimitivePreview(this->currentObjectToAdd, distance, position);
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
    if (found && this->cursor->getCursorMode() == CursorMode::NAVIGATION) {
      if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftCtrl))) {
        this->sceneManager.get()->clickSelectionSceneObject(maybeObject.value());
      } else {
        this->sceneManager.get()->setSelectedSceneObject(maybeObject.value());
      }

    } else if (found && this->cursor->getCursorMode() == CursorMode::REMOVING) {
      this->sceneManager.get()->removeObject(maybeObject.value()); // TODO : Ajouter une nouvelle m�thode pour supprimer un objet
      this->cursor->setCursorMode(CursorMode::NAVIGATION);

    } else if (this->cursor->getCursorMode() == CursorMode::ADDING) {
      this->sceneManager.get()->addElement(ray, distance, position, this->currentObjectToAdd);
      this->cursor->setCursorMode(CursorMode::NAVIGATION);
      this->sceneManager.get()->setSelectedSceneObject(this->sceneManager.get()->getObjects().back().get());
    }
  }
}
