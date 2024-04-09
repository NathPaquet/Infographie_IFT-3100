#include "scene2D.h"

#include "constants.h"

void Scene2D::setup() {
  // this->camera.setDistance(Constants::DEFAULT_CAMERA_DISTANCE);
  this->ray = Ray();
  this->camera.removeAllInteractions();
  this->camera.disableMouseInput();

  ofDisableLighting();
}

void Scene2D::update() {
  this->computeRay(this->camera, this->ray);
}

void Scene2D::drawScene() {
  ofPushStyle();

  this->camera.begin();

  this->sceneManager->drawScene();

  if (this->currentObjectToAdd != ElementType::NONE) {
    this->drawObjectPreview();
  }

  this->camera.end();

  ofPopStyle();
}

void Scene2D::dragObjectWithMouse() {
  if (draggedObject != nullptr) {
    const auto position = (this->ray.getOrigin() + this->ray.getDirection() * (Constants::DEFAULT_DISTANCE_TO_DRAW / abs(ray.getDirection().z)));
    this->draggedObject->setPosition(position);
  }
}

bool Scene2D::attemptToClickOnObjectWithMouse() {
  auto &&maybeObject = this->getObjectCollidingWithRay(this->sceneManager.get()->getObjects(), this->camera, this->ray);
  auto &&found = maybeObject.has_value();

  if (found) {
    if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftCtrl))) {
      this->sceneManager.get()->clickSelectionSceneObject(maybeObject.value());
    } else {
      this->sceneManager.get()->setSelectedSceneObject(maybeObject.value());
    }

    auto it = std::find(this->sceneManager.get()->getSelectedObjects().begin(), this->sceneManager.get()->getSelectedObjects().end(), maybeObject.value());

    if (it != this->sceneManager.get()->getSelectedObjects().end()) {
      draggedObject = *it;
      const auto position = (this->ray.getOrigin() + this->ray.getDirection() * (Constants::DEFAULT_DISTANCE_TO_DRAW / abs(ray.getDirection().z)));
      draggedObject->setDraggingPositionOnObject(position);
    }
  }
  return found;
}

bool Scene2D::attemptToAddObjectWithMouse() {
  const auto position = (this->ray.getOrigin() + this->ray.getDirection() * (Constants::DEFAULT_DISTANCE_TO_DRAW / abs(ray.getDirection().z)));
  if (this->wasDrawingFirstPositionClicked) {
    this->sceneManager->addElement(this->drawingFirstPosition, position, this->currentObjectToAdd);
    this->sceneManager->setSelectedSceneObject(this->sceneManager->getObjects().front().get());
    this->currentObjectToAdd = ElementType::NONE;
  } else {
    this->drawingFirstPosition = position;
  }
  this->wasDrawingFirstPositionClicked = !this->wasDrawingFirstPositionClicked;
  return !this->wasDrawingFirstPositionClicked;
}

bool Scene2D::attemptToRemoveObjectWihMouse() {
  auto &&maybeObject = this->getObjectCollidingWithRay(this->sceneManager.get()->getObjects(), this->camera, this->ray);
  auto &&found = maybeObject.has_value();

  if (found) {
    this->sceneManager.get()->removeObject(maybeObject.value());
  }
  return found;
}

void Scene2D::releaseDraggedObject() {
  shouldDragObject = false;
  this->draggedObject->releaseObjectFromDragging();
  this->draggedObject = nullptr;
}

void Scene2D::drawObjectPreview() {
  if (this->wasDrawingFirstPositionClicked) {
    auto position = (this->ray.getOrigin() + this->ray.getDirection() * (Constants::DEFAULT_DISTANCE_TO_DRAW / abs(ray.getDirection().z)));
    this->ray.drawPrimitivePreview(this->currentObjectToAdd, this->drawingFirstPosition, position);
  }
}

void Scene2D::moveCameraWithMouse() {
  this->camera.setPosition(this->camera.getPosition() + glm::vec3(ofGetPreviousMouseX() - ofGetMouseX(), ofGetMouseY() - ofGetPreviousMouseY(), 0) * 0.2);
}

void Scene2D::moveSelectedObjectsWithKey(int key) {
  if (hasADraggedObject()) {
    return;
  }

  for (const auto &selectedSceneObject : sceneManager.get()->getSelectedObjects()) {
    const auto &position = selectedSceneObject->getPosition();

    switch (key) {
      case OF_KEY_UP:
        selectedSceneObject->setPosition(position + glm::vec3(0, 1, 0));
        break;
      case OF_KEY_DOWN:
        selectedSceneObject->setPosition(position + glm::vec3(0, -1, 0));
        break;
      case OF_KEY_LEFT:
        selectedSceneObject->setPosition(position + glm::vec3(-1, 0, 0));
        break;
      case OF_KEY_RIGHT:
        selectedSceneObject->setPosition(position + glm::vec3(1, 0, 0));
        break;
      default:
        break;
    }
  }
}
