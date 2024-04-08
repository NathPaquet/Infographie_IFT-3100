#pragma once
#include "scene.h"

#include <lights/types/AmbientLight.h>

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
  void moveObjectWithScrollOnly(float scrollAmount);
  void releaseDraggedObject();
  void drawObjectPreview();

  AmbientLight &getAmbientLight();

private:
  const float SCROLL_POWER = 2.f;

  std::unique_ptr<ofEasyCam> perspectiveCamera;
  std::unique_ptr<ofEasyCam> orthographicCamera;
  ofEasyCam *currentCamera;
  Ray ray;
  AmbientLight ambientLight;
  ofSpherePrimitive sphere = ofSpherePrimitive(20, 60, OF_PRIMITIVE_TRIANGLES);

  void setupPerspectiveCamera();
  void setupOrthographicCamera();
};
