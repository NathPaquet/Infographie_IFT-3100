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

void Scene2D::update() {
}

void Scene2D::drawScene() {
  ofPushStyle();
  // ofBackground(this->backgroundColor);
  this->camera.begin();
  this->processMouseActions();
  this->sceneManager->drawScene();
  this->camera.end();
  ofPopStyle();
}

void Scene2D::processMouseActions() {
  // if (!isMouseClickInScene()) {
  //   return;
  // }
  // const float distance = Constants::DEFAULT_DISTANCE_TO_DRAW;
  //
  // if (this->cursor->getCursorMode() == CursorMode::ADDING) {
  //   auto &&maybeObject = this->cursor->setRayWithCollidingObject(this->sceneManager->getObjects(), this->camera, this->ray);
  //   auto &&found = maybeObject.has_value();
  //   auto position = (this->ray.getOrigin() + this->ray.getDirection() * (distance / abs(ray.getDirection().z)));
  //
  //   if (this->wasDrawingFirstPositionClicked && !found) {
  //     this->ray.drawPrimitivePreview(this->currentObjectToAdd, this->drawingFirstPosition, position);
  //   }
  // }
  //
  // if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
  //   shouldDragObject = false;
  //   this->draggedObject = nullptr;
  // }
  //
  // if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
  //   auto &&maybeObject = this->cursor->setRayWithCollidingObject(this->sceneManager->getObjects(), this->camera, this->ray);
  //   auto &&found = maybeObject.has_value();
  //
  //   if (found) {
  //     auto it = std::find(this->sceneManager->getSelectedObjects().begin(), this->sceneManager->getSelectedObjects().end(), maybeObject.value());
  //
  //     if (it != this->sceneManager->getSelectedObjects().end()) {
  //       draggedObject = *it;
  //       shouldDragObject = true;
  //     }
  //   }
  //
  //   if (found && this->cursor->getCursorMode() == CursorMode::NAVIGATION) {
  //     if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftCtrl))) {
  //       this->sceneManager->clickSelectionSceneObject(maybeObject.value());
  //     } else {
  //       this->sceneManager->setSelectedSceneObject(maybeObject.value());
  //     }
  //
  //   } else if (found && this->cursor->getCursorMode() == CursorMode::REMOVING) {
  //     this->sceneManager->removeObject(maybeObject.value());
  //     this->cursor->setCursorMode(CursorMode::NAVIGATION);
  //
  //   } else if (this->cursor->getCursorMode() == CursorMode::ADDING) {
  //     const auto position = (this->ray.getOrigin() + this->ray.getDirection() * (distance / abs(ray.getDirection().z)));
  //     if (this->wasDrawingFirstPositionClicked) {
  //       this->sceneManager->addElement(this->drawingFirstPosition, position, this->currentObjectToAdd);
  //       this->cursor->setCursorMode(CursorMode::NAVIGATION);
  //       this->sceneManager->setSelectedSceneObject(this->sceneManager->getObjects().front().get());
  //     } else {
  //       this->drawingFirstPosition = position;
  //     }
  //     this->wasDrawingFirstPositionClicked = !this->wasDrawingFirstPositionClicked;
  //   }
  // }
  //
  // if (ImGui::IsMouseDown(ImGuiMouseButton_Left)
  //     && shouldDragObject
  //     && this->cursor->getCursorMode() == CursorMode::NAVIGATION) {
  //   this->cursor->computeRay(this->camera, this->ray);
  //   const auto position = (this->ray.getOrigin() + this->ray.getDirection() * (distance / abs(ray.getDirection().z)));
  //
  //   this->sceneManager->setObjectPosition(this->draggedObject, position);
  // }
}
