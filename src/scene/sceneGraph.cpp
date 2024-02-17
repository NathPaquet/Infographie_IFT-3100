#include "sceneGraph.h"

SceneGraph::SceneGraph(SceneManager &sceneManager):
    sceneManager(sceneManager) {
}

void SceneGraph::drawSceneGraphElement() {
  const auto &sceneObjects = sceneManager.getObjects();
  for (const auto &sceneObjectPtr : sceneObjects) {
    const SceneObject &sceneObject = *sceneObjectPtr;
    ImGui::Text("Un objet test");
  }
}
