#pragma once

#include "SceneElementFactory.h"
#include "ofMain.h"
#include "sceneObject.h"

class SceneManager {
public:
  SceneManager(const ofEasyCam *camera);
  ~SceneManager();

  void addElement(const ofVec3f &position, const ElementType primitiveType);
  void removeObject(const SceneObject *sceneObject);
  void removeAllSelectedObjects();
  void drawScene();
  const std::vector<std::unique_ptr<SceneObject>> &getObjects() const;
  void setSelectedSceneObject(const SceneObject *sceneObject);
  void clickSelectionSceneObject(const SceneObject *sceneObject);
  const std::vector<SceneObject *> &getSelectedObject() const;
  std::vector<SceneObject *> &getSelectedObjectReference();
  void setObjectPosition(const SceneObject *object, const ofVec3f &position);

  const ofEasyCam *camera;

private:
  void clearScene();

  std::vector<SceneObject *> selectedSceneObjects;
  std::vector<std::unique_ptr<SceneObject>> sceneObjects;
};
