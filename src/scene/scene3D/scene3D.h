#pragma once
#include "cubemap/skybox.h"
#include "scene.h"

class Scene3D : public Scene {
public:
  Scene3D(std::unique_ptr<SceneManager> sceneManager):
      Scene(std::move(sceneManager)) {}
  void setup() override;
  void update() override;
  void drawScene() override;
  void drawSceneFromCamera(const glm::vec3 &cameraPosition);
  inline void activateCameraMouseInput() {
    this->currentCamera->enableMouseInput();
  }
  inline void deactivateCameraMouseInput() {
    this->currentCamera->disableMouseInput();
  }
  void toggleProjectionMode();
  void toggleSkyboxActivation();
  void loadSkybox(const string &texturePath);
  bool attemptToClickOnObjectWithMouse();
  bool attemptToAddObjectWithMouse();
  bool attemptToRemoveObjectWihMouse();
  void dragObjectWithMouse();
  void moveObjectWithScrollOnly(float scrollAmount);
  void releaseDraggedObject();
  void drawObjectPreview();

private:
  const float SCROLL_POWER = 2.f;

  ofLight light;
  std::unique_ptr<ofEasyCam> perspectiveCamera;
  std::unique_ptr<ofEasyCam> orthographicCamera;
  ofEasyCam *currentCamera;
  Skybox skybox;
  bool isSkyboxEnabled = false;
  Ray ray;
  ofSpherePrimitive sphere = ofSpherePrimitive(20, 60, OF_PRIMITIVE_TRIANGLES);

  void setupPerspectiveCamera();
  void setupOrthographicCamera();

  bool needToUpdateDynamicEnvironmentMap{true};
  Cubemap dynamicEnvironmentMap;
  ofShader shader;
  ofEasyCam cameraDynamicEnvironmentMap;

  void configureCameraForFace(int faceIndex);
};
