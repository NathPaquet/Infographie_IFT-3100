#include "scene3D.h"

#include "constants.h"
#include "utils/LoadingScreen.h"

Scene3D::~Scene3D() {
}

void Scene3D::setup() {
  this->sphere.enableTextures();
  this->ray = Ray();
  this->ambientLight = AmbientLight();

  ofEnableSmoothing();
  ofEnableLighting();

  /*this->light.setAmbientColor(Constants::AMBIANT_COLOR);
  this->light.setPosition(Constants::LIGHT_POSITION);
  this->light.enable();*/

  // Initialize camera
  this->setupPerspectiveCamera();
  this->setupOrthographicCamera();

  this->currentCamera = this->perspectiveCamera.get();

  // Set up reflective shader
  this->reflectionShader.load("shaders/reflectionShader.vert", "shaders/reflectionShader.frag");

  // Set up refraction shader
  this->refractionShader.load("shaders/refractionShader.vert", "shaders/refractionShader.frag");
}

void Scene3D::update() {
  this->sceneManager->updateObjectProperties();

  this->computeRay(*this->currentCamera, this->ray);

  if (this->isIntersectionPointDisplay) {
    this->getObjectCollidingWithRay(this->sceneManager->getObjects(), *this->currentCamera, this->ray);
  }

  if (this->frameNumberToUpdateEnvironmentCubemap == ofGetFrameNum()) {
    this->lowQualityRenderer.updateEnvironmentCubemap();
  }
}

void Scene3D::drawScene() {
  this->currentCamera->begin();

  if (this->skybox.isEnabled() && !this->skybox.isSkyboxLoaded()) {
    string message = "Skybox texture not loaded yet";
    LoadingScreen::drawLoadingScreen(message);
  }

  this->drawSceneFromCamera(this->currentCamera->getGlobalPosition());

  if (this->isIntersectionPointDisplay) {
    this->drawIntersectionPoint(*this->currentCamera, this->ray);
  }

  this->currentCamera->end();
}

void Scene3D::drawSceneFromCamera(const glm::vec3 &cameraPosition) {
  if (this->skybox.isEnabled() && this->skybox.isSkyboxLoaded() && this->currentCamera == this->perspectiveCamera.get()) {
    this->skybox.draw(Constants::DEFAULT_SKYBOX_SIZE, cameraPosition);
  }

  this->sceneManager->drawScene();

  if (this->currentObjectToAdd != ElementType::NONE) {
    this->drawObjectPreview();
  }

  if (this->currentCamera == this->perspectiveCamera.get()) {
    if (this->isReflectionSphereEnabled) {
      this->drawReflectiveSphere(cameraPosition);
    }
    if (this->isRefractionSphereEnabled) {
      this->drawRefractionSphere(cameraPosition);
    }
  }
}

void Scene3D::setFrameToUpdateEnvironmentCubemap() {
  if (this->isReflectionSphereEnabled || this->isRefractionSphereEnabled) {
    this->frameNumberToUpdateEnvironmentCubemap = ofGetFrameNum() + 1;
  }
}

void Scene3D::toggleProjectionMode() {
  if (this->currentCamera->getOrtho()) {
    this->perspectiveCamera.get()->enableMouseInput();
    this->orthographicCamera.get()->disableMouseInput();
    this->currentCamera = this->perspectiveCamera.get();
  } else {
    this->perspectiveCamera.get()->disableMouseInput();
    this->orthographicCamera.get()->enableMouseInput();
    this->currentCamera = this->orthographicCamera.get();
  }
}

void Scene3D::toggleSkyboxActivation() {
  this->skybox.toggleSkyboxActivation();
}

void Scene3D::loadSkybox(const string &skyboxTexturePath) {
  this->skybox.loadTexture(skyboxTexturePath);
}

bool Scene3D::attemptToClickOnObjectWithMouse() {
  auto &&maybeObject = this->getObjectCollidingWithRay(this->sceneManager.get()->getObjects(), *this->currentCamera, this->ray);
  auto &&found = maybeObject.has_value();

  if (found) {
    if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftCtrl))) {
      this->sceneManager.get()->clickSelectionSceneObject(maybeObject.value());
    } else {
      this->sceneManager.get()->setSelectedSceneObject(maybeObject.value());
    }

    auto it = std::find(this->sceneManager.get()->getSelectedObjects().begin(), this->sceneManager.get()->getSelectedObjects().end(), maybeObject.value());

    if (it != this->sceneManager.get()->getSelectedObjects().end()) {
      draggedObject = *it;
    }
  }
  return found;
}

bool Scene3D::attemptToAddObjectWithMouse() {
  this->sceneManager.get()->addElement(this->ray.getOrigin() + this->ray.getDirection() * Constants::DEFAULT_DISTANCE_TO_DRAW, this->currentObjectToAdd);
  this->sceneManager.get()->setSelectedSceneObject(this->sceneManager.get()->getObjects().front().get());
  this->currentObjectToAdd = ElementType::NONE;
  return true;
}

bool Scene3D::attemptToRemoveObjectWihMouse() {
  auto &&maybeObject = this->getObjectCollidingWithRay(this->sceneManager.get()->getObjects(), *this->currentCamera, this->ray);
  auto &&found = maybeObject.has_value();

  if (found) {
    this->sceneManager.get()->removeObject(maybeObject.value());
  }
  return found;
}

void Scene3D::dragObjectWithMouse() {
  if (hasADraggedObject()) {
    this->draggedObject->setPosition(ray.getOrigin() + ray.getDirection() * Constants::DEFAULT_DISTANCE_TO_DRAW);
  }
}

void Scene3D::moveObjectWithScrollOnly(float scrollAmount) {
  if (hasADraggedObject()) {
    auto direction = ray.getDirection() * scrollAmount * Constants::SCROLL_POWER;
    this->draggedObject->setPosition(this->draggedObject->getPosition() + direction);
  }
}

void Scene3D::releaseDraggedObject() {
  shouldDragObject = false;
  this->draggedObject = nullptr;
}

void Scene3D::drawObjectPreview() {
  // auto &&maybeObject = this->getObjectCollidingWithRay(this->sceneManager.get()->getObjects(), *this->currentCamera, this->ray);
  // auto &&found = maybeObject.has_value();
  auto position = this->ray.getOrigin() + this->ray.getDirection() * Constants::DEFAULT_DISTANCE_TO_DRAW;

  this->ray.drawPrimitiveDefaultPreview(this->currentObjectToAdd, position);
}

bool Scene3D::isAmbientLightEnable() const {
  return this->ambientLight.isEnable();
}

void Scene3D::toggleAmbientLight() {
  this->ambientLight.toggle();
}

void Scene3D::setupPerspectiveCamera() {
  this->perspectiveCamera = std::make_unique<ofEasyCam>();

  this->perspectiveCamera.get()->setNearClip(Constants::DEFAULT_CAMERA_NEAR_CLIP);
  this->perspectiveCamera.get()->setPosition(200, 50, 200);
  this->perspectiveCamera.get()->lookAt(glm::vec3(0, 0, 0));
}

void Scene3D::setupOrthographicCamera() {
  this->orthographicCamera = std::make_unique<ofEasyCam>();
  this->orthographicCamera.get()->enableOrtho();

  this->orthographicCamera.get()->setPosition(10, 5, 10);
  this->orthographicCamera.get()->lookAt(glm::vec3(0, 0, 0));

  this->orthographicCamera.get()->removeAllInteractions();
  this->orthographicCamera.get()->addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_XY, OF_MOUSE_BUTTON_LEFT);
  this->orthographicCamera.get()->addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_Z, OF_MOUSE_BUTTON_RIGHT);

  this->orthographicCamera.get()->setNearClip(-1000000);
  this->orthographicCamera.get()->setFarClip(1000000);
}

void Scene3D::deactivateCenterSphere() {
  this->isReflectionSphereEnabled = false;
  this->isRefractionSphereEnabled = false;
}

void Scene3D::activateReflectionSphere() {
  this->isReflectionSphereEnabled = true;
  this->isRefractionSphereEnabled = false;
}

void Scene3D::activateRefractionSphere() {
  this->isRefractionSphereEnabled = true;
  this->isReflectionSphereEnabled = false;
}

void Scene3D::drawReflectiveSphere(const glm::vec3 &cameraPosition) {
  // Render reflective object with reflective shader and environment map
  this->reflectionShader.begin();

  this->reflectionShader.setUniform3f("cameraPosition", cameraPosition);
  this->reflectionShader.setUniform1i("environmentMap", 0);

  glBindTexture(GL_TEXTURE_CUBE_MAP, this->lowQualityRenderer.getCubemapTextureID());

  int defaultSphereResolution = ofGetSphereResolution();
  ofSetSphereResolution(100);
  ofDrawSphere(0, 0, 0, 20);
  ofSetSphereResolution(defaultSphereResolution);

  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

  this->reflectionShader.end();
}

void Scene3D::drawRefractionSphere(const glm::vec3 &cameraPosition) {
  // Render refractive object with refractive shader and environment map
  this->refractionShader.begin();

  this->refractionShader.setUniform3f("cameraPosition", cameraPosition);
  this->refractionShader.setUniform1i("environmentMap", 0);

  glBindTexture(GL_TEXTURE_CUBE_MAP, this->lowQualityRenderer.getCubemapTextureID());

  int defaultSphereResolution = ofGetSphereResolution();
  ofSetSphereResolution(100);
  ofDrawSphere(0, 0, 0, 20);
  ofSetSphereResolution(defaultSphereResolution);

  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

  this->refractionShader.end();
}