#include "sceneManager.h"

#include "ImHelpers.h"
#include "object/object3D/CubicPlanet.h"
#include "object/object3D/Planet.h"
#include "ofxImGui.h"

SceneManager::SceneManager() {
  ofLogNotice("SceneManager") << "SceneManager constructor";
}

SceneManager::~SceneManager() {
  clearScene();
}

void SceneManager::addElement(const glm::vec3 position,  const ElementType primitiveType) {
  this->sceneObjects.emplace_front(SceneObjectFactory::createDefaultSceneObject(position, primitiveType));
}

void SceneManager::addElement(const glm::vec3 position, const glm::vec3 outerPosition, const ElementType primitiveType) {
  this->sceneObjects.emplace_front(SceneObjectFactory::createSceneObject(position, outerPosition, primitiveType));
}

void SceneManager::removeObject(const SceneObject *sceneObject) {
  auto it = std::find_if(this->sceneObjects.begin(), this->sceneObjects.end(), [&](auto &&obj) { return obj.get() == sceneObject; });
  auto selectedIt = std::find(this->selectedSceneObjects.begin(), this->selectedSceneObjects.end(), sceneObject);

  if (it != this->sceneObjects.end()) {
    this->sceneObjects.erase(it);
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
    }
  }

  this->selectedSceneObjects.clear();
}

void SceneManager::drawScene() {
  for (auto &&element : this->sceneObjects) {
    bool isSelected = std::find(this->selectedSceneObjects.begin(), this->selectedSceneObjects.end(), element.get()) != this->selectedSceneObjects.end();
    element.get()->draw(isSelected);
  }
}

const std::list<std::unique_ptr<SceneObject>> &SceneManager::getObjects() const {
  return this->sceneObjects;
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
  it->get()->setPosition(position);

  ofLogNotice("object dragged to") << position.x << "," << position.y << "," << position.z;
}
