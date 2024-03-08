#pragma once
#include "Cursor.h"
#include "scene/sceneManager.h"

class Scene {
public:
  Scene(std::unique_ptr<SceneManager> sceneManager,
      Cursor *cursor):
      sceneManager(std::move(sceneManager)),
      cursor(cursor) {}
  virtual void setup() = 0;
  virtual void drawScene() = 0;

  SceneManager *getSceneManager();
  void removeAllSelectedObjects();
  vector<SceneObject *> getSelectedObjectsReference();
  bool hasCurrentObjectToAdd();
  void setCurrentObjectToAdd(ElementType elementType);

protected:
  bool isMouseClickInScene();

  std::unique_ptr<SceneManager> sceneManager;
  Cursor *cursor;
  bool shouldDragObject = false;
  ElementType currentObjectToAdd = ElementType::NONE;
};
