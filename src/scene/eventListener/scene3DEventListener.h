#pragma once
#include "sceneeventlistener.h"
class Scene3DEventListener : public SceneEventListener {
public:
  void processMouseActions() override;
};
