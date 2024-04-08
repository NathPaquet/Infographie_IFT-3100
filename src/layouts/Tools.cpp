#include "Tools.h"

Tools::Tools(Scene3D *scene3D):
    scene3D(scene3D) {
}

void Tools::createToolsMenu() {
  if (ImGui::BeginMenu("Tools")) {
    if (ImGui::MenuItem("Export")) {
      showExportMenu = true;
    }

    std::string ambientLightTitle = (scene3D->getAmbientLight().isEnable() ? "Disable" : "Enable") + std::string(" Ambient Light");
    if (ImGui::MenuItem(ambientLightTitle.c_str())) {
      scene3D->getAmbientLight().toggle();
    }

    ImGui::EndMenu();
  }

  if (showExportMenu) {
    exportMenu.createExportMenu(&showExportMenu);
  }
}
