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

void Scene::computeRay(const ofEasyCam &camera, Ray &ray) const {
  auto mouseWorldDirection = findMouseDirectionInWorld(camera);
  const glm::vec3 cameraPositionInScreen(ofGetMouseX(), ofGetMouseY(), 0);
  auto &&cameraPostionInWorld = camera.screenToWorld(cameraPositionInScreen);
  ray.set(cameraPostionInWorld, mouseWorldDirection);
}

glm::highp_vec3 Scene::findMouseDirectionInWorld(const ofEasyCam &camera) const {
  const glm::vec3 screenMouse0(ofGetMouseX(), ofGetMouseY(), 0);
  const glm::vec3 screenMouse1(ofGetMouseX(), ofGetMouseY(), 1);
  auto &&worldMouse0 = camera.screenToWorld(screenMouse0);
  auto &&worldMouse1 = camera.screenToWorld(screenMouse1);
  auto &&worldMouseDirection = worldMouse1 - worldMouse0;
  return worldMouseDirection;
}

std::optional<const SceneObject *> Scene::setRayWithCollidingObject(const std::list<std::unique_ptr<SceneObject>> &objects, const ofEasyCam &camera, Ray &ray) {
  this->computeRay(camera, ray);

  glm::vec2 baricentricCoordinates;
  float distance;
  float distanceToClosestIntersection = numeric_limits<float>::max();
  const SceneObject *foundSceneObject{nullptr};
  for (auto &&object : objects) {
    bool intersects = ray.isRayCollidingWithPrimitive(object.get()->getPrimitive(), baricentricCoordinates, distance);
    if (intersects && (distance < distanceToClosestIntersection)) {
      foundSceneObject = object.get();
      distanceToClosestIntersection = distance;
    }
  }
  return foundSceneObject ? std::optional(foundSceneObject) : std::nullopt;
}
