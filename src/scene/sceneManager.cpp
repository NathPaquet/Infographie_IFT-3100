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

  auto cameraPtr = this->sceneObjects.front().get();
  addCamera(cameraPtr, primitiveType);
}

void SceneManager::addElement(const glm::vec3 position, const glm::vec3 outerPosition, const ElementType primitiveType) {
  this->sceneObjects.emplace_front(SceneObjectFactory::createSceneObject(position, outerPosition, primitiveType));
}

void SceneManager::addCamera(const SceneObject *sceneObject, const ElementType primitiveType) {
  if (primitiveType == ElementType::CAMERA) {
    auto camera = (Camera *)sceneObject; // dynamic_cast<Camera *>(sceneObject);
    this->cameras.push_back(camera);
  }
}

void SceneManager::removeCamera(const SceneObject *sceneObject) {
  for (int i = 0; i < cameras.size(); i++) {
    if (cameras.at(i) == sceneObject) {
      this->cameras.erase(cameras.begin() + i);
      return;
    }
  }
}

void SceneManager::removeObject(const SceneObject *sceneObject) {
  auto it = std::find_if(this->sceneObjects.begin(), this->sceneObjects.end(), [&](auto &&obj) { return obj.get() == sceneObject; });
  auto selectedIt = std::find(this->selectedSceneObjects.begin(), this->selectedSceneObjects.end(), sceneObject);

  if (it != this->sceneObjects.end()) {
    this->sceneObjects.erase(it);
    removeCamera(sceneObject);
  }
  if (selectedIt != this->selectedSceneObjects.end()) {
    this->selectedSceneObjects.erase(selectedIt);
  }
}

void SceneManager::removeAllSelectedObjects() {
  for (auto &&selectedObject : this->selectedSceneObjects) {
    auto it = std::find_if(this->sceneObjects.begin(), this->sceneObjects.end(), [&](auto &&obj) { return obj.get() == selectedObject; });
    if (it != this->sceneObjects.end()) {
      this->sceneObjects.erase(it);
      removeCamera(selectedObject);
    }
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
}

void SceneManager::setObjectPosition(const SceneObject *object, const ofVec3f &position) {
  auto it = std::find_if(this->sceneObjects.begin(), this->sceneObjects.end(), [&](auto &&obj) { return obj.get() == object; });
  if (it != this->sceneObjects.end()) {
    it->get()->setPosition(position);
    ofLogNotice("object dragged to") << position.x << "," << position.y << "," << position.z;
  }
}

void SceneManager::toggleActivationBoundingBox() {
  this->isBoundingBoxEnabled = !this->isBoundingBoxEnabled;
}

void SceneManager::toggleActivationObjectAxis() {
  this->isObjectAxisEnabled = !this->isObjectAxisEnabled;
}
