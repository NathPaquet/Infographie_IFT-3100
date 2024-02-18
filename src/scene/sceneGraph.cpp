#include "sceneGraph.h"

SceneGraph::SceneGraph(SceneManager &sceneManager):
    sceneManager(sceneManager) {
}

void SceneGraph::drawSceneGraphElements() {
  const auto &sceneObjects = sceneManager.getObjects();

  int count = 0;
  float elementBoxHeight = 50.0f;
  static int item_current_idx = 0;

  for (const auto &sceneObjectPtr : sceneObjects) {
    count++;
    const SceneObject &sceneObject = *sceneObjectPtr;

    bool isSelected = (&sceneObject == sceneManager.getSelectedObject());

    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 2.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 2.0f);

    if (isSelected) {
      ImGui::PushStyleColor(ImGuiCol_Border, (ImVec4)ImColor(209, 45, 73, 255));
      ImGui::PushStyleColor(ImGuiCol_ChildBg, (ImVec4)ImColor(209, 45, 73, 100));
    }

    ImGui::BeginChild(("Object " + std::to_string(count)).c_str(), ImVec2(ImGui::GetContentRegionAvail().x, elementBoxHeight), true);

    ImGui::Text("Objet numero %d", count);

    ImGui::PopStyleVar(2);
    if (isSelected) {
      ImGui::PopStyleColor(2);
    }

    ImGui::EndChild();

    if (ImGui::IsItemClicked()) {
      ofLogNotice("SceneGraph") << "Objet numero " << count << " cliqué";
      sceneManager.setSelectedSceneObject(&sceneObject);
    }
  }
}
