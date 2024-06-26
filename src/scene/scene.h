#pragma once
#include "Cursor.h"
#include "scene/sceneManager.h"

#include <optional>

class Scene {
public:
  Scene(std::unique_ptr<SceneManager> sceneManager):
      sceneManager(std::move(sceneManager)) {}
  virtual void setup() = 0;
  virtual void update() = 0;
  virtual void drawScene() = 0;

  SceneManager *getSceneManager();
  void removeAllSelectedObjects();
  void clearScene();
  vector<SceneObject *> getSelectedObjectsReference();
  bool hasCurrentObjectToAdd();
  void setCurrentObjectToAdd(ElementType elementType);
  void toggleIntersectionPointDisplay() {
    isIntersectionPointDisplay = !isIntersectionPointDisplay;
  }
  const bool getIsIntersectionPointDisplay() const {
    return isIntersectionPointDisplay;
  }

  const bool getIsBoundingBoxEnabled() const {
    return sceneManager->getIsBoundingBoxEnabled();
  }

  const bool getIsObjectAxisEnabled() const {
    return sceneManager->getIsObjectAxisEnabled();
  }

protected:
  bool isMouseClickInScene();
  bool hasADraggedObject() const;

  void computeRay(const ofEasyCam &camera, Ray &ray) const;
  glm::highp_vec3 findMouseDirectionInWorld(const ofEasyCam &camera) const;
  std::optional<const SceneObject *> getObjectCollidingWithRay(const std::list<std::unique_ptr<SceneObject>> &objects, const ofEasyCam &camera, Ray &ray);

  bool isIntersectionPointDisplay{false};
  void drawIntersectionPoint(const ofEasyCam &camera, const Ray &ray) const;

  std::unique_ptr<SceneManager> sceneManager;
  bool shouldDragObject = false;
  SceneObject *draggedObject = nullptr;
  ElementType currentObjectToAdd = ElementType::NONE;
  float lastIntersectionDistance;
};
