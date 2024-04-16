﻿#include "scene3D.h"

#include "constants.h"

void Scene3D::setup() {
  this->sphere.enableTextures();
  this->ray = Ray();

  // Initialize light
  this->light.setAmbientColor(Constants::AMBIANT_COLOR);
  this->light.setPosition(Constants::LIGHT_POSITION);
  ofEnableSmoothing();
  ofEnableLighting();
  this->light.enable();

  // Initialize camera
  this->setupPerspectiveCamera();
  this->setupOrthographicCamera();

  this->currentCamera = this->perspectiveCamera.get();

  // Set up reflective shader
  this->shader.load("shaders/reflectiveShader.vert", "shaders/reflectiveShader.frag");

  // Set up dynamic environment map camera
  this->cameraDynamicEnvironmentMap.disableMouseInput();
  this->cameraDynamicEnvironmentMap.setPosition(-100, 100, -100);
  this->cameraDynamicEnvironmentMap.setNearClip(100);
  this->cameraDynamicEnvironmentMap.setFarClip(1000);
  this->cameraDynamicEnvironmentMap.setFov(90);
  this->cameraDynamicEnvironmentMap.setAspectRatio(1);
}

void Scene3D::update() {
  this->computeRay(*this->currentCamera, this->ray);

  if (ImGui::IsMouseClicked(ImGuiMouseButton_Middle)) {
    needToUpdateDynamicEnvironmentMap = true;
  }

  // Update dynamic environment map
  // Create an array of 6 images, one for each face of the cubemap
  if (needToUpdateDynamicEnvironmentMap) {
    std::array<ofImage, 6> cubemapImages;
    for (int i = 0; i < 6; i++) {
      configureCameraForFace(i);
      this->cameraDynamicEnvironmentMap.begin();
      this->drawSceneFromCamera(this->cameraDynamicEnvironmentMap.getGlobalPosition());
      // Save the image of the current face (i) of the cubemap in a 2048x2048 image
      // cubemapImages[i].allocate(2048, 2048, OF_IMAGE_COLOR);
      int size = 500;
      cubemapImages[i].grabScreen((ofGetWidth() - size) / 2, (ofGetHeight() - size) / 2, size, size);
      cubemapImages[i].setImageType(OF_IMAGE_COLOR);
      cubemapImages[i].getPixels().swapRgb();

      cubemapImages[i].saveImage("cubemap" + std::to_string(i) + ".png");

      this->cameraDynamicEnvironmentMap.end();
    }
    this->dynamicEnvironmentMap.setCubemapImage(cubemapImages[0], cubemapImages[1], cubemapImages[2], cubemapImages[3], cubemapImages[4], cubemapImages[5]);
    this->dynamicEnvironmentMap.enableCubemapTextures();

    needToUpdateDynamicEnvironmentMap = false;
  }
}

void Scene3D::configureCameraForFace(int faceIndex) {
  switch (faceIndex) {
    case 0: // Droite
      this->cameraDynamicEnvironmentMap.lookAt(glm::vec3(1, 0, 0));
      break;
    case 1: // Gauche
      this->cameraDynamicEnvironmentMap.lookAt(glm::vec3(-1, 0, 0));
      break;
    case 2: // Haut
      this->cameraDynamicEnvironmentMap.lookAt(glm::vec3(0, 1, 0));
      break;
    case 3: // Bas
      this->cameraDynamicEnvironmentMap.lookAt(glm::vec3(0, -1, 0));
      break;
    case 4: // Devant
      this->cameraDynamicEnvironmentMap.lookAt(glm::vec3(0, 0, 1));
      break;
    case 5: // Derrière
      this->cameraDynamicEnvironmentMap.lookAt(glm::vec3(0, 0, -1));
      break;
    default:
      break;
  }
}

void Scene3D::drawScene() {
  this->currentCamera->begin();

  this->drawSceneFromCamera(this->currentCamera->getGlobalPosition());

  this->currentCamera->end();
}

void Scene3D::drawSceneFromCamera(const glm::vec3 &cameraPosition) {
  if (this->isSkyboxEnabled && this->currentCamera == this->perspectiveCamera.get()) {
    this->skybox.draw(Constants::DEFAULT_SKYBOX_SIZE, cameraPosition);
  }

  // ofDrawGrid(10, 100, false, false, true, false);

  ofDrawSphere(0, -100, 0, 10);

  this->sceneManager.get()->drawScene();

  if (this->currentObjectToAdd != ElementType::NONE) {
    this->drawObjectPreview();
  }

  // Render reflective object with reflective shader and environment map
  this->shader.begin();

  this->shader.setUniform3f("cameraPosition", cameraPosition);
  this->shader.setUniform1i("skybox", 0);

  glBindTexture(GL_TEXTURE_CUBE_MAP, this->dynamicEnvironmentMap.getTextureObjectID());

  ofDrawBox(-100, 100, -100, 100);

  // ofDrawSphere(0, 0, 0, 20);

  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

  this->shader.end();
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
  this->isSkyboxEnabled = !this->isSkyboxEnabled;
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
  auto &&maybeObject = this->getObjectCollidingWithRay(this->sceneManager.get()->getObjects(), *this->currentCamera, this->ray);
  auto &&found = maybeObject.has_value();

  if (!found) {
    this->sceneManager.get()->addElement(this->ray.getOrigin() + this->ray.getDirection() * Constants::DEFAULT_DISTANCE_TO_DRAW, this->currentObjectToAdd);
    this->sceneManager.get()->setSelectedSceneObject(this->sceneManager.get()->getObjects().front().get());
    this->currentObjectToAdd = ElementType::NONE;
  }
  return !found;
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
  auto &&maybeObject = this->getObjectCollidingWithRay(this->sceneManager.get()->getObjects(), *this->currentCamera, this->ray);
  auto &&found = maybeObject.has_value();
  auto position = this->ray.getOrigin() + this->ray.getDirection() * Constants::DEFAULT_DISTANCE_TO_DRAW;

  if (!found) {
    this->ray.drawPrimitiveDefaultPreview(this->currentObjectToAdd, position);
  }
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
