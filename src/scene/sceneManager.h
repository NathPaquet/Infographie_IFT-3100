#pragma once

#include "ofMain.h"
#include "sceneObject.h"

class SceneManager {
public:
  SceneManager();
  ~SceneManager();

  void addElement(const ofVec3f &position);
  void removeElement(size_t index);
  void drawScene();
  void drawPropertiesPanel();
  const std::vector<std::unique_ptr<SceneObject>> &getObjects() const;
  void setSelectedSceneObject(const SceneObject *sceneObject);

private:
  void clearScene();

  SceneObject *selectedSceneOject{nullptr};
  std::vector<std::unique_ptr<SceneObject>> sceneElements;
};
