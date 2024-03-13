#include "CameraPanel.h"

CameraPanel::CameraPanel(SceneManager *sceneManager, WindowCamera *windowCamera):
    sceneManager(sceneManager), windowCamera(windowCamera){};

void CameraPanel::setSceneManager(SceneManager *sceneManager) {
  this->sceneManager = sceneManager;
  windowCamera->setSelectedCamera(nullptr);
}

void CameraPanel::create() {
  if (ImGui::BeginMenu("Cameras")) {
    auto &cameras = sceneManager->getCameras();

    if (cameras.empty()) {
      ImGui::Text("No cameras");
    } else {
      for (const auto &camera : cameras) {
        std::stringstream ss;

        if (windowCamera->getSelectedCamera() == camera) {
          ss << "-> ";
        }

        ss << "Camera (ID : " << camera << ")";
        std::string cameraName = ss.str();

        if (ImGui::MenuItem(cameraName.c_str())) {
          windowCamera->setSelectedCamera(camera);
        }
      }
    }

    bool isWindowCameraShown = windowCamera->getIsShow();
    if (ImGui::Checkbox("Show camera view", &isWindowCameraShown)) {
      windowCamera->switchIsShown();
    }

    ImGui::EndMenu();
  }
}
