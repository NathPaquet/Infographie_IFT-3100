#pragma once
#include "scene.h"
class Scene2D : public Scene {
public:
  Scene2D(std::unique_ptr<SceneManager> sceneManager,
      std::unique_ptr<SceneEventListener> sceneEventListener,
      Cursor *cursor):
      Scene(std::move(sceneManager), std::move(sceneEventListener), cursor) {}
  void setup() override;
  void drawScene() override;

private:
  void processMouseActions();
  ofEasyCam camera;
  Ray ray;
  ofColor backgroundColor = ofColor(255,255,255,255);
  const float object_distance = 200.f;
};
