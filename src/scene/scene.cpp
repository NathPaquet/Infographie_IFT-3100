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

void Scene::setCurrentObjectToAdd(ElementType elementType) {
  this->currentObjectToAdd = elementType;
}

bool Scene::isMouseClickInScene() {
  return ofGetMouseX() > Constants::SCENE_GRAPH_WIDTH && ofGetMouseX() < ofGetWidth() - Constants::PROPERTIES_PANEL_WIDTH;
}
