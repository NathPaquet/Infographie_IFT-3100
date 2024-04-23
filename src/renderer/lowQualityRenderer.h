#pragma once

#include "cubemap/skybox.h"
#include "ofThread.h"

#include <cubemap/cubemap.h>
#include <sceneManager.h>

class LowQualityRenderer {
public:
  LowQualityRenderer() = default;
  LowQualityRenderer(const SceneManager *sceneManager, const Skybox *skybox);

  void updateEnvironmentCubemap();
  const unsigned int getCubemapTextureID() const;

private:
  const SceneManager *sceneManager{nullptr};
  const Skybox *skybox{nullptr};

  // ofGLProgrammableRenderer renderer;

  Cubemap environmentCubemap;
  array<ofImage, 6> environmentCubemapImages;
  array<ofCamera, 6> environmentMapCameras;

  void setupEnvironmentMapCameras();
  void configureEnvironmentMapCameraOrientation(int faceIndex, ofCamera &currentCamera);
  void ajustEnvironmentMapPicture(int faceIndex, ofImage &environmentMapImage);
};
