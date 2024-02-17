#pragma once
#include "sceneManager.h"

class SceneGraph {
public:
  SceneGraph(SceneManager &sceneManager);

private:
  SceneManager &sceneManager;
};
