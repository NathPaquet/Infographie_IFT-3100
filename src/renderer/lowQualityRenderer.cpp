#include "lowQualityRenderer.h"

constexpr int RIGHT_FACE_INDEX = 0;
constexpr int LEFT_FACE_INDEX = 1;
constexpr int TOP_FACE_INDEX = 2;
constexpr int BOTTOM_FACE_INDEX = 3;
constexpr int FRONT_FACE_INDEX = 4;
constexpr int BACK_FACE_INDEX = 5;

LowQualityRenderer::LowQualityRenderer(const SceneManager *sceneManager) {
  this->sceneManager = sceneManager;

  this->setupEnvironmentMapCameras();
}

void LowQualityRenderer::updateEnvironmentCubemap() {
  for (int i = 0; i < 6; i++) {
    ofClear(0, 0, 0, 0);

    this->environmentMapCameras[i].begin();

    // Display the skybox
    // if (this->isSkyboxEnabled) {
    //  this->skybox.draw(10000, this->cameraDynamicEnvironmentMap.getGlobalPosition());
    //}

    // Display the scene
    this->sceneManager->drawScene();

    this->environmentMapCameras[i].end();

    // Save the image
    int size = min(ofGetWidth(), ofGetHeight());
    environmentCubemapImages[i].grabScreen((ofGetWidth() - size) / 2, (ofGetHeight() - size) / 2, size, size);
    environmentCubemapImages[i].setImageType(OF_IMAGE_COLOR);
    environmentCubemapImages[i].getPixels().swapRgb();
    ajustEnvironmentMapPicture(i, environmentCubemapImages[i]);
  }
  this->environmentCubemap.setCubemapImage(environmentCubemapImages[0], environmentCubemapImages[1], environmentCubemapImages[2], environmentCubemapImages[3], environmentCubemapImages[4], environmentCubemapImages[5]);
  this->environmentCubemap.enableCubemapTextures();
}

const unsigned int LowQualityRenderer::getCubemapTextureID() const {
  return this->environmentCubemap.getTextureObjectID();
}

void LowQualityRenderer::setupEnvironmentMapCameras() {
  for (int i = 0; i < this->environmentMapCameras.size(); ++i) {
    this->environmentMapCameras[i].setPosition(0, 0, 0);
    this->environmentMapCameras[i].setNearClip(20.0);
    this->environmentMapCameras[i].setFarClip(10000);
    this->environmentMapCameras[i].setFov(90);
    this->configureEnvironmentMapCameraOrientation(i, this->environmentMapCameras[i]);
  }
}

void LowQualityRenderer::configureEnvironmentMapCameraOrientation(int faceIndex, ofCamera &currentCamera) {
  switch (faceIndex) {
    case RIGHT_FACE_INDEX: // Droite
      currentCamera.lookAt(currentCamera.getGlobalPosition() + glm::vec3(1, 0, 0));
      break;
    case LEFT_FACE_INDEX: // Gauche
      currentCamera.lookAt(currentCamera.getGlobalPosition() + glm::vec3(-1, 0, 0));
      break;
    case TOP_FACE_INDEX: // Haut
      currentCamera.lookAt(currentCamera.getGlobalPosition() + glm::vec3(0, 1, 0));
      break;
    case BOTTOM_FACE_INDEX: // Bas
      currentCamera.lookAt(currentCamera.getGlobalPosition() + glm::vec3(0, -1, 0));
      break;
    case FRONT_FACE_INDEX: // Devant
      currentCamera.lookAt(currentCamera.getGlobalPosition() + glm::vec3(0, 0, 1));
      break;
    case BACK_FACE_INDEX: // Derrière
      currentCamera.lookAt(currentCamera.getGlobalPosition() + glm::vec3(0, 0, -1));
      break;
    default:
      break;
  }
}

void LowQualityRenderer::ajustEnvironmentMapPicture(int faceIndex, ofImage &environmentMapImage) {
  switch (faceIndex) {
    case RIGHT_FACE_INDEX: // Droite
      environmentMapImage.mirror(false, true);
      break;
    case LEFT_FACE_INDEX: // Gauche
      environmentMapImage.mirror(false, true);
      break;
    case TOP_FACE_INDEX: // Haut
      environmentMapImage.mirror(true, false);
      break;
    case BOTTOM_FACE_INDEX: // Bas
      environmentMapImage.mirror(true, false);
      break;
    case FRONT_FACE_INDEX: // Devant
      environmentMapImage.mirror(false, true);
      break;
    case BACK_FACE_INDEX: // Derrière
      environmentMapImage.mirror(false, true);
      break;
    default:
      break;
  }
}
