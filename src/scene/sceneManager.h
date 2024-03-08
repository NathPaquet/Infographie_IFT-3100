#pragma once

#include "object/SceneObjectFactory.h"
#include "object/object3D/Camera.h"
#include "object/sceneObject.h"
#include "ofMain.h"
#include "ray.h"

class SceneManager {
public:
  SceneManager();
  ~SceneManager();

  void addElement(const glm::vec3 position, const ElementType primitiveType);
  void addElement(const glm::vec3 position, const glm::vec3 outerPosition, const ElementType primitiveType);

  void removeObject(const SceneObject *sceneObject);
  void removeAllSelectedObjects();
  void drawScene();
  const std::list<std::unique_ptr<SceneObject>> &getObjects() const;
  const std::vector<Camera *> &getCameras() const;
  void setSelectedSceneObject(const SceneObject *sceneObject);
  void clickSelectionSceneObject(const SceneObject *sceneObject);
  const std::vector<SceneObject *> &getSelectedObjects() const;
  std::vector<SceneObject *> &getSelectedObjectsReference();
  void setObjectPosition(const SceneObject *object, const ofVec3f &position);
  void toggleActivationBoundingBox();
  void toggleActivationObjectAxis();

private:
  void clearScene();
  void addCamera(const SceneObject *sceneObject, const ElementType primitiveType);
  void removeCamera(const SceneObject *sceneObject);

  bool isBoundingBoxEnabled = false;
  bool isObjectAxisEnabled = false;
  std::vector<SceneObject *> selectedSceneObjects;
  std::vector<Camera *> cameras;
  std::list<std::unique_ptr<SceneObject>> sceneObjects;
};
