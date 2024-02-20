#pragma once
#include "sceneManager.h"

class SceneGraph {
public:
  SceneGraph(SceneManager &sceneManager);

  void drawSceneGraphElements();

private:
  SceneManager &sceneManager;
};
