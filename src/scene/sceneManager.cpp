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
  sceneElements.emplace_back(SceneElementFactory::createSceneObject(position, primitiveType));
}

void SceneManager::removeElement(const SceneObject *sceneObject) {
  auto it = std::find_if(this->sceneElements.begin(), this->sceneElements.end(), [&](auto &&obj) { return obj.get() == sceneObject; });
  if (it->get() == this->selectedSceneOject) {
    this->selectedSceneOject = nullptr;
  }
  sceneElements.erase(it);
}

void SceneManager::drawScene() {
  for (const auto &element : sceneElements) {
    bool isSelected = element.get() == this->selectedSceneOject;
    element.get()->draw(isSelected);
  }
}

void SceneManager::drawPropertiesPanel() {
  ImGui::Text("Object Properties :");
  ImGui::Separator();
  if (!this->selectedSceneOject) {
    return;
  }
  ImGui::BeginGroup();
  this->selectedSceneOject->draw_properties();
  ImGui::EndGroup();
}

const std::vector<std::unique_ptr<SceneObject>> &SceneManager::getObjects() const {
  return this->sceneElements;
}

void SceneManager::setSelectedSceneObject(const SceneObject *sceneObject) {
  auto it = std::find_if(this->sceneElements.begin(), this->sceneElements.end(), [&](auto &&obj) { return obj.get() == sceneObject; });
  this->selectedSceneOject = it->get();
}

const SceneObject *SceneManager::getSelectedObject() const {
  return this->selectedSceneOject;
}

void SceneManager::clearScene() {
  this->selectedSceneOject = nullptr;
  sceneElements.clear();
}
