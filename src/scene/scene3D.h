#pragma once
#include "scene.h"
class Scene3D : public Scene {
public:
  Scene3D(std::unique_ptr<SceneManager> sceneManager,
      Cursor *cursor):
      Scene(std::move(sceneManager), cursor) {}
  void setup() override;
  void drawScene() override;
  void toggleProjectionMode();

private:
  ofLight light;
  std::unique_ptr<ofEasyCam> perspectiveCamera;
  std::unique_ptr<ofEasyCam> orthographicCamera;
  ofEasyCam *currentCamera;
  Ray ray;
  ofSpherePrimitive sphere = ofSpherePrimitive(20, 60, OF_PRIMITIVE_TRIANGLES);
  SceneObject *draggedObject = nullptr;

  void processMouseActions();
  void setupPerspectiveCamera();
  void setupOrthographicCamera();
};
