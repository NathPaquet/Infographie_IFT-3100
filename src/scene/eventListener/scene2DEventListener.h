#pragma once
#include "sceneeventlistener.h"
class Scene2DEventListener : public SceneEventListener {
public:
  void processMouseActions() override;
};
