#include "scene.h"

#include "constants.h"

SceneManager *Scene::getSceneManager() {
  return this->sceneManager.get();
}

void Scene::removeAllSelectedObjects() {
  this->sceneManager->removeAllSelectedObjects();
}

vector<SceneObject *> Scene::getSelectedObjectsReference() {
  return this->sceneManager->getSelectedObjectsReference();
}

bool Scene::hasCurrentObjectToAdd() {
  return this->currentObjectToAdd != ElementType::NONE;
}

void Scene::setCurrentObjectToAdd(ElementType elementType) {
  this->currentObjectToAdd = elementType;
}

bool Scene::isMouseClickInScene() {
  return !ImGui::GetIO().WantCaptureMouse;
}
