#include "loadingScreen.h"

#include "ofxImGui.h"

void LoadingScreen::drawLoadingScreen() {
  ImGui::OpenPopup("LoadingScreen");

  ImVec2 center = ImGui::GetMainViewport()->GetCenter();
  ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

  if (ImGui::BeginPopupModal("LoadingScreen", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
    ImGui::Text("Loading in progress.");

    ImGui::EndPopup();
  }
}
