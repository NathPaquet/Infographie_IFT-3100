#include "scene3D.h"

#include "constants.h"

void Scene3D::setup() {
  this->sphere.enableTextures();
  this->camera.setDistance(Constants::DEFAULT_CAMERA_DISTANCE);
  this->ray = Ray();

  // Initialize light
  this->light.setAmbientColor(Constants::AMBIANT_COLOR);
  this->light.setPosition(Constants::LIGHT_POSITION);
  ofEnableSmoothing();
  ofEnableLighting();
  this->light.enable();
}

void Scene3D::drawScene() {
  this->cursor->drawCursor(ofGetMouseX(), ofGetMouseY());

  camera.begin();

  ofDrawGrid(100, 10, false, false, false, true);
  this->sceneManager.get()->drawScene();

  this->processMouseActions();

  camera.end();
}

void Scene3D::processMouseActions() {
  if (this->shouldDragObject) {
    this->camera.disableMouseInput();
  }
  if (!isMouseClickInScene()) {
    this->camera.disableMouseInput();
    return;
  }

  auto &&maybeObject = this->cursor->setRayWithCollidingObject(this->sceneManager.get()->getObjects(), this->camera, this->ray);
  auto &&found = maybeObject.has_value();
  const float distance = Constants::DEFAULT_DISTANCE_TO_DRAW_PRIMITIVE;
  auto position = this->ray.getOrigin() + this->ray.getDirection() * distance;

  if (!found && this->cursor->getCursorMode() == CursorMode::ADDING) {
    this->ray.drawPrimitivePreview(this->currentObjectToAdd, distance, position);
  }

  if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
    shouldDragObject = false;
    this->camera.enableMouseInput();
  }

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
      this->sceneManager.get()->addElement(ray, distance, this->ray.getOrigin() + this->ray.getDirection() * distance, this->currentObjectToAdd);
      this->cursor->setCursorMode(CursorMode::NAVIGATION);
      this->sceneManager.get()->setSelectedSceneObject(this->sceneManager.get()->getObjects().back().get());
    }
  }
}

glm::highp_vec3 Scene3D::findMouseClick3DPosition() const {
  const glm::vec3 screenMouse(ofGetMouseX(), ofGetMouseY(), 0);
  auto &&worldMouse = camera.screenToWorld(screenMouse);
  auto &&worldMouseEnd = camera.screenToWorld(glm::vec3(screenMouse.x, screenMouse.y, 1.0f));
  auto &&worldMouseDirection = worldMouseEnd - worldMouse;
  return worldMouseDirection;
}
