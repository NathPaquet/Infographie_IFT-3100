#include "Tools.h"

void Tools::createToolsMenu() {
  if (ImGui::BeginMenu("Tools")) {
    if (ImGui::MenuItem("Export")) {
      showExportMenu = true;
    }

    ImGui::EndMenu();
  }

  if (showExportMenu) {
    exportMenu.createExportMenu(&showExportMenu);
  }
}
