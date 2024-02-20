#include "sceneManager.h"

#include "CubicPlanet.h"
#include "ImHelpers.h"
#include "Planet.h"
#include "ofxImGui.h"

SceneManager::SceneManager() {
  ofLogNotice("SceneManager") << "SceneManager constructor";
}

SceneManager::~SceneManager() {
  clearScene();
}

void SceneManager::addElement(const ofVec3f &position, const ElementType primitiveType) {
  this->sceneObjects.emplace_back(SceneElementFactory::createSceneObject(position, primitiveType));
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

void SceneManager::drawPropertiesPanel() {
  // TODO : Implement this
  // ImGui::Text("Object Properties :");
  // ImGui::Separator();
  // if (!this->selectedSceneOject) {
  //   return;
  // }
  // ImGui::BeginGroup();
  // this->selectedSceneOject->draw_properties();
  // ImGui::EndGroup();
}

const std::vector<std::unique_ptr<SceneObject>> &SceneManager::getObjects() const {
  return this->sceneObjects;
}

void SceneManager::setSelectedSceneObject(const SceneObject *sceneObject) {
  auto it = std::find_if(this->sceneObjects.begin(), this->sceneObjects.end(), [&](auto &&obj) { return obj.get() == sceneObject; });
  if (it != this->sceneObjects.end()) {
    this->selectedSceneObjects.clear();
    this->selectedSceneObjects.push_back(it->get());
  }
}

void SceneManager::addSelectedSceneObject(const SceneObject *sceneObject) {
  auto it = std::find_if(this->sceneObjects.begin(), this->sceneObjects.end(), [&](auto &&obj) { return obj.get() == sceneObject; });
  if (it != this->sceneObjects.end()) {
    this->selectedSceneObjects.push_back(it->get());
  }
}

const std::vector<SceneObject *> &SceneManager::getSelectedObject() const {
  return this->selectedSceneObjects;
}

const SceneObject *SceneManager::getSelectedObject() const {
  return this->selectedSceneOject;
}

void SceneManager::clearScene() {
  this->selectedSceneObjects.clear();
  this->sceneObjects.clear();
}
