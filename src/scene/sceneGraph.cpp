#include "sceneGraph.h"

SceneGraph::SceneGraph(SceneManager &sceneManager):
    sceneManager(sceneManager) {
}

void SceneGraph::drawSceneGraphElement() {
  const auto &sceneObjects = sceneManager.getObjects();

  int count = 0;
  float elementBoxHeight = 50.0f;

  for (const auto &sceneObjectPtr : sceneObjects) {
    count++;
    const SceneObject &sceneObject = *sceneObjectPtr;

    bool isSelected = (&sceneObject == sceneManager.getSelectedObject());

    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 2.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);

    if (isSelected) {
      ImGui::PushStyleColor(ImGuiCol_Border, (ImVec4)ImColor(255, 0, 0, 255));
    }

    ImGui::BeginChild(("Object " + std::to_string(count)).c_str(), ImVec2(ImGui::GetContentRegionAvail().x, elementBoxHeight), true);

    ImGui::Text("Objet numero %d", count);

    if (isSelected) {
      ImGui::PopStyleColor();
    }
    ImGui::EndChild();

    ImGui::PopStyleVar(2);
  }
}
