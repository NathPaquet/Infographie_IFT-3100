#pragma once
#include "scene.h"
class Scene3D : public Scene {
public:
  Scene3D(std::unique_ptr<SceneManager> sceneManager):
      Scene(std::move(sceneManager)) {}
  void setup() override;
  void update() override;
  void drawScene() override;
  inline void activateCameraMouseInput() {
    this->currentCamera->enableMouseInput();
  }
  inline void deactivateCameraMouseInput() {
    this->currentCamera->disableMouseInput();
  }
  void toggleProjectionMode();
  bool attemptToClickOnObjectWithMouse();
  bool attemptToAddObjectWithMouse();
  bool attemptToRemoveObjectWihMouse();
  void dragObjectWithMouse();
  void moveObjectWithScroll(float scrollAmount);
  void releaseDraggedObject();
  void drawObjectPreview();

private:
  const float SCROLL_POWER = 2.f;

  ofLight light;
  std::unique_ptr<ofEasyCam> perspectiveCamera;
  std::unique_ptr<ofEasyCam> orthographicCamera;
  ofEasyCam *currentCamera;
  Ray ray;
  ofSpherePrimitive sphere = ofSpherePrimitive(20, 60, OF_PRIMITIVE_TRIANGLES);
  SceneObject *draggedObject = nullptr;

  void setupPerspectiveCamera();
  void setupOrthographicCamera();
  bool hasADraggedObject() const;
};
