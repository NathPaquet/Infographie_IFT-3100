#pragma once
#include "Cursor.h"
#include "eventListener/sceneEventListener.h"
#include "scene/sceneManager.h"

class Scene {
public:
  Scene(std::unique_ptr<SceneManager> sceneManager,
      std::unique_ptr<SceneEventListener> sceneEventListener,
      Cursor *cursor):
      sceneManager(std::move(sceneManager)),
      sceneEventListener(std::move(sceneEventListener)),
      cursor(cursor) {}
  virtual void setup() = 0;
  virtual void drawScene() = 0;

  SceneManager *getSceneManager();
  void removeAllSelectedObjects();
  vector<SceneObject *> getSelectedObjectsReference();
  void setCurrentObjectToAdd(ElementType elementType);

protected:
  bool isMouseClickInScene();

  std::unique_ptr<SceneManager> sceneManager;
  std::unique_ptr<SceneEventListener> sceneEventListener;
  Cursor *cursor;
  bool shouldDragObject = false;
  ElementType currentObjectToAdd;
};
