#pragma once

#include "SceneElementFactory.h"
#include "ofMain.h"
#include "sceneObject.h"

class SceneManager {
public:
  SceneManager();
  ~SceneManager();

  void addElement(const ofVec3f &position, const ElementType primitiveType);
  void removeObject(const SceneObject *sceneObject);
  void removeAllSelectedObjects();
  void drawScene();
  void drawPropertiesPanel();
  const std::vector<std::unique_ptr<SceneObject>> &getObjects() const;
  void setSelectedSceneObject(const SceneObject *sceneObject);
  void addSelectedSceneObject(const SceneObject *sceneObject);
  const std::vector<SceneObject *> &getSelectedObject() const;

private:
  void clearScene();
  std::vector<SceneObject *> selectedSceneObjects;
  std::vector<std::unique_ptr<SceneObject>> sceneObjects;
};
