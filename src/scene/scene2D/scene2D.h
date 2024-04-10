#pragma once
#include "scene.h"

class Scene2D : public Scene {
public:
  Scene2D(std::unique_ptr<SceneManager> sceneManager):
      Scene(std::move(sceneManager)) {}
  void setup() override;
  void update() override;
  void drawScene() override;
  void dragObjectWithMouse();
  bool attemptToClickOnObjectWithMouse();
  bool attemptToAddObjectWithMouse();
  bool attemptToRemoveObjectWihMouse();
  void releaseDraggedObject();
  void drawObjectPreview();
  void moveCameraWithMouse();
  void moveSelectedObjectsWithKey(int key);
  void stopMovingObjectWithKey();

private:
  ofEasyCam camera;
  Ray ray;
  ofColor backgroundColor = ofColor(255, 255, 255, 255);
  const float object_distance = 200.f;
  glm::vec3 drawingFirstPosition;
  bool wasDrawingFirstPositionClicked = false;
};
