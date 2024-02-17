#pragma once
#include "sceneManager.h"

class SceneGraph {
public:
  SceneGraph(SceneManager &sceneManager);

  void drawSceneGraphElement();

private:
  SceneManager &sceneManager;
};
