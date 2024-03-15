#include "scene3D.h"

#include "constants.h"

void Scene3D::setup() {
  this->sphere.enableTextures();
  this->ray = Ray();

  // Initialize light
  this->light.setAmbientColor(Constants::AMBIANT_COLOR);
  this->light.setPosition(Constants::LIGHT_POSITION);
  ofEnableSmoothing();
  ofEnableLighting();
  this->light.enable();

  // Initialize camera
  this->setupPerspectiveCamera();
  this->setupOrthographicCamera();

  this->currentCamera = this->perspectiveCamera.get();
}

void Scene3D::update() {
  this->computeRay(*this->currentCamera, this->ray);
}

void Scene3D::drawScene() {
  this->currentCamera->begin();

  ofDrawGrid(10, 100, false, false, true, false);

  ofDrawSphere(0, 0, 0, 10);
  this->sceneManager.get()->drawScene();

  if (this->currentObjectToAdd != ElementType::NONE) {
    this->drawObjectPreview();
  }

  this->currentCamera->end();
}

void Scene3D::toggleProjectionMode() {
  if (this->currentCamera->getOrtho()) {
    this->perspectiveCamera.get()->enableMouseInput();
    this->orthographicCamera.get()->disableMouseInput();
    this->currentCamera = this->perspectiveCamera.get();
  } else {
    this->perspectiveCamera.get()->disableMouseInput();
    this->orthographicCamera.get()->enableMouseInput();
    this->currentCamera = this->orthographicCamera.get();
  }
}

bool Scene3D::attemptToClickOnObjectWithMouse() {
  auto &&maybeObject = this->getObjectCollidingWithRay(this->sceneManager.get()->getObjects(), *this->currentCamera, this->ray);
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
    }
  }
  return found;
}

bool Scene3D::attemptToAddObjectWithMouse() {
  auto &&maybeObject = this->getObjectCollidingWithRay(this->sceneManager.get()->getObjects(), *this->currentCamera, this->ray);
  auto &&found = maybeObject.has_value();

  if (!found) {
    this->sceneManager.get()->addElement(this->ray.getOrigin() + this->ray.getDirection() * Constants::DEFAULT_DISTANCE_TO_DRAW, this->currentObjectToAdd);
    this->sceneManager.get()->setSelectedSceneObject(this->sceneManager.get()->getObjects().front().get());
    this->currentObjectToAdd = ElementType::NONE;
  }
  return !found;
}

bool Scene3D::attemptToRemoveObjectWihMouse() {
  auto &&maybeObject = this->getObjectCollidingWithRay(this->sceneManager.get()->getObjects(), *this->currentCamera, this->ray);
  auto &&found = maybeObject.has_value();

  if (found) {
    this->sceneManager.get()->removeObject(maybeObject.value());
  }
  return found;
}

void Scene3D::dragObjectWithMouse() {
  if (hasADraggedObject()) {
    this->draggedObject->setPosition(ray.getOrigin() + ray.getDirection() * Constants::DEFAULT_DISTANCE_TO_DRAW);
  }
}

void Scene3D::moveObjectWithScroll(float scrollAmount) {
  if (hasADraggedObject()) {
    auto direction = ray.getDirection() * scrollAmount * SCROLL_POWER;
    this->draggedObject->setPosition(this->draggedObject->getPosition() + direction);
  }
}

void Scene3D::releaseDraggedObject() {
  shouldDragObject = false;
  this->draggedObject = nullptr;
}

void Scene3D::drawObjectPreview() {
  auto &&maybeObject = this->getObjectCollidingWithRay(this->sceneManager.get()->getObjects(), *this->currentCamera, this->ray);
  auto &&found = maybeObject.has_value();
  auto position = this->ray.getOrigin() + this->ray.getDirection() * Constants::DEFAULT_DISTANCE_TO_DRAW;

  if (!found) {
    this->ray.drawPrimitiveDefaultPreview(this->currentObjectToAdd, position);
  }
}

void Scene3D::setupPerspectiveCamera() {
  this->perspectiveCamera = std::make_unique<ofEasyCam>();

  this->perspectiveCamera.get()->setNearClip(Constants::DEFAULT_CAMERA_NEAR_CLIP);
  this->perspectiveCamera.get()->setPosition(200, 50, 200);
  this->perspectiveCamera.get()->lookAt(glm::vec3(0, 0, 0));
}

void Scene3D::setupOrthographicCamera() {
  this->orthographicCamera = std::make_unique<ofEasyCam>();
  this->orthographicCamera.get()->enableOrtho();

  this->orthographicCamera.get()->setPosition(10, 5, 10);
  this->orthographicCamera.get()->lookAt(glm::vec3(0, 0, 0));

  this->orthographicCamera.get()->removeAllInteractions();
  this->orthographicCamera.get()->addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_XY, OF_MOUSE_BUTTON_LEFT);
  this->orthographicCamera.get()->addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_Z, OF_MOUSE_BUTTON_RIGHT);

  this->orthographicCamera.get()->setNearClip(-1000000);
  this->orthographicCamera.get()->setFarClip(1000000);
}

bool Scene3D::hasADraggedObject() const {
  return this->draggedObject != nullptr;
}
