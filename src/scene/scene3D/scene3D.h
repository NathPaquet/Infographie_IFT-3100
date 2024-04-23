#pragma once
#include "cubemap/skybox.h"
#include "scene.h"

#include <renderer/lowQualityRenderer.h>

class Scene3D : public Scene {
public:
  Scene3D(std::unique_ptr<SceneManager> sceneManager):
      Scene(std::move(sceneManager)), lowQualityRenderer(this->sceneManager.get(), &this->skybox) {}
  ~Scene3D();
  void setup() override;
  void update() override;
  void drawScene() override;
  void drawSceneFromCamera(const glm::vec3 &cameraPosition);
  void drawLowQualityFromCameraObject(const ofCamera &camera) const;
  inline void activateCameraMouseInput() {
    this->currentCamera->enableMouseInput();
  }
  inline void deactivateCameraMouseInput() {
    this->currentCamera->disableMouseInput();
  }
  void updateEnvironnementCubmap();
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
  void deactivateCenterSphere();
  void activateReflectionSphere();
  void activateRefractionSphere();

private:
  const float SCROLL_POWER = 2.f;

  ofLight light;
  std::unique_ptr<ofEasyCam> perspectiveCamera;
  std::unique_ptr<ofEasyCam> orthographicCamera;
  ofEasyCam *currentCamera;
  Skybox skybox;
  bool isSkyboxLoaded{false};
  Ray ray;
  ofSpherePrimitive sphere = ofSpherePrimitive(20, 60, OF_PRIMITIVE_TRIANGLES);

  void setupPerspectiveCamera();
  void setupOrthographicCamera();
  void drawReflectiveSphere(const glm::vec3 &cameraPosition);
  void drawRefractionSphere(const glm::vec3 &cameraPosition);

  LowQualityRenderer lowQualityRenderer;

  bool isReflectionSphereEnabled{false};
  ofShader reflectionShader;
  bool isRefractionSphereEnabled{false};
  ofShader refractionShader;
};
