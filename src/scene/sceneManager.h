#pragma once

#include "SceneElementFactory.h"
#include "ofMain.h"
#include "sceneObject.h"

class SceneManager {
public:
  SceneManager();
  ~SceneManager();

  void addElement(const ofVec3f &position, const ElementType primitiveType);
  void removeElement(const SceneObject *sceneObject);
  void drawScene();
  void drawPropertiesPanel();
  const std::vector<std::unique_ptr<SceneObject>> &getObjects() const;
  void setSelectedSceneObject(const SceneObject *sceneObject);
  const SceneObject *getSelectedObject() const;

private:
  void clearScene();
  SceneObject *selectedSceneOject{nullptr};
  std::vector<std::unique_ptr<SceneObject>> sceneElements;
};
