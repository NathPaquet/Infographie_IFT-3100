#include "sceneManager.h"

#include "ImHelpers.h"
#include "Planet.h"
#include "ofxImGui.h"

SceneManager::SceneManager() {
  ofLogNotice("SceneManager") << "SceneManager constructor";
}

SceneManager::~SceneManager() {
  clearScene();
}

void SceneManager::addElement(const ofVec3f &position) {
  // TODO : Add scene object factory here
  sceneElements.emplace_back(std::make_unique<Planet>(Planet(position.x, position.y, position.z)));
}

void SceneManager::removeElement(size_t index) {
  if (index < 0 || index >= sceneElements.size()) {
    return;
  }
  sceneElements.erase(std::next(sceneElements.begin(), index));
}

void SceneManager::drawScene() {
  for (auto &&element : sceneElements) {
    element->draw();
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

void SceneManager::clearScene() {
  this->selectedSceneOject = nullptr;
  sceneElements.clear();
}
