#include "sceneGraph.h"

SceneGraph::SceneGraph(SceneManager &sceneManager):
    sceneManager(sceneManager) {
}

void SceneGraph::drawSceneGraphElements() {
  const auto &sceneObjects = sceneManager.getObjects();

  float elementBoxHeight = 50.0f;

  for (auto &&sceneObjectPtr : sceneObjects) {
    bool isSelected = std::find(sceneManager.getSelectedObject().begin(), sceneManager.getSelectedObject().end(), sceneObjectPtr.get()) != sceneManager.getSelectedObject().end();

    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 2.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 2.0f);

    if (isSelected) {
      ImGui::PushStyleColor(ImGuiCol_Border, (ImVec4)ImColor(209, 45, 73, 255));
      ImGui::PushStyleColor(ImGuiCol_ChildBg, (ImVec4)ImColor(209, 45, 73, 100));
    }

    ImGui::BeginChild(std::to_string(reinterpret_cast<uintptr_t>(sceneObjectPtr.get())).c_str(), ImVec2(ImGui::GetContentRegionAvail().x, elementBoxHeight), true);

    ImGui::Text("%s", typeid(*sceneObjectPtr).name());
    ImGui::Text("ID : %p", sceneObjectPtr.get());

    ImGui::PopStyleVar(2);
    if (isSelected) {
      ImGui::PopStyleColor(2);
    }

    ImGui::EndChild();

    if (ImGui::IsItemClicked()) {
      if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftCtrl))) {
        sceneManager.clickSelectionSceneObject(sceneObjectPtr.get());
      } else {
        sceneManager.setSelectedSceneObject(sceneObjectPtr.get());
      }
    }
  }
}
