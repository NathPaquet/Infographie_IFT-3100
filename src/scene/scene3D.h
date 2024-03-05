#pragma once
#include "scene.h"
class Scene3D : public Scene {
public:
  Scene3D(std::unique_ptr<SceneManager> sceneManager,
      std::unique_ptr<SceneEventListener> sceneEventListener,
      Cursor *cursor):
      Scene(std::move(sceneManager), std::move(sceneEventListener), cursor) {}
  void setup() override;
  void drawScene() override;

private:
  ofLight light;
  ofEasyCam camera;
  Ray ray;
  ofSpherePrimitive sphere = ofSpherePrimitive(20, 60, OF_PRIMITIVE_TRIANGLES);

  void processMouseActions();
  glm::highp_vec3 findMouseClick3DPosition() const;
};