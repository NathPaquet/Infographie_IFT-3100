#include "sceneManager.h"

#include "ImHelpers.h"
#include "object/object3D/primitive/CubicPlanet.h"
#include "object/object3D/primitive/Planet.h"
#include "ofxImGui.h"

SceneManager::SceneManager() {
  ofLogNotice("SceneManager") << "SceneManager constructor";
}

SceneManager::~SceneManager() {
  clearScene();
}

void SceneManager::addElement(const glm::vec3 position, const ElementType primitiveType) {
  this->sceneObjects.emplace_front(SceneObjectFactory::createDefaultSceneObject(position, primitiveType));

  auto sceneObjectPtr = this->sceneObjects.front().get();
  addIfCamera(sceneObjectPtr, primitiveType);
}

void SceneManager::addElement(const glm::vec3 position, const glm::vec3 outerPosition, const ElementType primitiveType) {
  this->sceneObjects.emplace_front(SceneObjectFactory::createSceneObject(position, outerPosition, primitiveType));

  auto sceneObjectPtr = this->sceneObjects.front().get();
  addIfCamera(sceneObjectPtr, primitiveType);
}

void SceneManager::addIfCamera(const SceneObject *sceneObject, const ElementType primitiveType) {
  if (primitiveType == ElementType::CAMERA) {
    auto camera = (Camera *)sceneObject;
    this->cameras.push_back(camera);
  }
}

void SceneManager::removeElement(const SceneObject *sceneObject) {
  auto it = std::find_if(this->sceneObjects.begin(), this->sceneObjects.end(), [&](auto &&obj) { return obj.get() == sceneObject; });

  if (it != this->sceneObjects.end()) {
    this->sceneObjects.erase(it);
  }
}

void SceneManager::removeSelectedElement(const SceneObject *sceneObject) {
  auto selectedIt = std::find(this->selectedSceneObjects.begin(), this->selectedSceneObjects.end(), sceneObject);

  if (selectedIt != this->selectedSceneObjects.end()) {
    this->selectedSceneObjects.erase(selectedIt);
  }
}

void SceneManager::attemptToRemoveObjectFromCameras(const SceneObject *sceneObject) {
  auto camIt = std::find(this->cameras.begin(), this->cameras.end(), sceneObject);

  if (camIt != this->cameras.end()) {
    this->cameras.erase(camIt);
  }
}

void SceneManager::removeObject(const SceneObject *sceneObject) {
  removeElement(sceneObject);
  removeSelectedElement(sceneObject);
  attemptToRemoveObjectFromCameras(sceneObject);
}

void SceneManager::removeAllSelectedObjects() {
  for (auto &&selectedObject : this->selectedSceneObjects) {
    removeElement(selectedObject);
    attemptToRemoveObjectFromCameras(selectedObject);
  }

  this->selectedSceneObjects.clear();
}

void SceneManager::drawScene() {
  for (auto &&element : this->sceneObjects) {
    bool isSelected = std::find(this->selectedSceneObjects.begin(), this->selectedSceneObjects.end(), element.get()) != this->selectedSceneObjects.end();
    element.get()->draw(isSelected, this->isBoundingBoxEnabled, this->isObjectAxisEnabled);
  }
}

const std::list<std::unique_ptr<SceneObject>> &SceneManager::getObjects() const {
  return this->sceneObjects;
}

const std::vector<Camera *> &SceneManager::getCameras() const {
  return this->cameras;
}

void SceneManager::setSelectedSceneObject(const SceneObject *sceneObject) {
  auto it = std::find_if(this->sceneObjects.begin(), this->sceneObjects.end(), [&](auto &&obj) { return obj.get() == sceneObject; });
  if (it != this->sceneObjects.end()) {
    this->selectedSceneObjects.clear();
    this->selectedSceneObjects.push_back(it->get());
  }
}

void SceneManager::clickSelectionSceneObject(const SceneObject *sceneObject) {
  auto it = std::find_if(this->sceneObjects.begin(), this->sceneObjects.end(), [&](auto &&obj) { return obj.get() == sceneObject; });
  if (it != this->sceneObjects.end()) {
    if (std::find(this->selectedSceneObjects.begin(), this->selectedSceneObjects.end(), it->get()) != this->selectedSceneObjects.end()) {
      this->selectedSceneObjects.erase(std::remove(this->selectedSceneObjects.begin(), this->selectedSceneObjects.end(), it->get()), this->selectedSceneObjects.end());
    } else {
      this->selectedSceneObjects.push_back(it->get());
    }
  }
}

const std::vector<SceneObject *> &SceneManager::getSelectedObjects() const {
  return this->selectedSceneObjects;
}

std::vector<SceneObject *> &SceneManager::getSelectedObjectsReference() {
  return this->selectedSceneObjects;
}

void SceneManager::clearScene() {
  this->selectedSceneObjects.clear();
  this->sceneObjects.clear();
  this->cameras.clear();
}

void SceneManager::toggleActivationBoundingBox() {
  this->isBoundingBoxEnabled = !this->isBoundingBoxEnabled;
}

void SceneManager::toggleActivationObjectAxis() {
  this->isObjectAxisEnabled = !this->isObjectAxisEnabled;
}
