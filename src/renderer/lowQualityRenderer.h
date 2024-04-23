#pragma once

#include "ofThread.h"

#include <sceneManager.h>

class LowQualityRenderer : public ofThread {
public:
  LowQualityRenderer();

  void threadedFunction() override;

private:
  SceneManager *sceneManager;
};
