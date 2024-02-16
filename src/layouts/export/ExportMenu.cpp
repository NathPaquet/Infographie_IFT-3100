#include "ExportMenu.h"

void ExportMenu::createExportMenu(bool *show) {
  ImGui::Begin("Export menu", show);

  if (ImGui::BeginTabBar("ExportTab")) {
    createExportImageTabItem();
    createExportSequenceTabItem();

    ImGui::EndTabBar();
  }

  ImGui::End();
}

void ExportMenu::createExportImageTabItem() {
  if (ImGui::BeginTabItem("Export image")) {
    if (ImGui::Button("Take screenshot")) {
      imageCapture.takeScreenshot();
    }

    ImGui::EndTabItem();
  }
}

void ExportMenu::createExportSequenceTabItem() {
  if (ImGui::BeginTabItem("Export sequence")) {
    ImGui::SliderInt("Duration (seconds)", &duration, 1, 10);
    ImGui::Separator();
    ImGui::SliderFloat("Step (seconds)", &step, 0.25f, 1.0f, "%.2f", 0.25f);
    ImGui::Separator();

    numberOfImages = duration / step;
    ImGui::Text("Number of images: %d", numberOfImages);
    ImGui::Separator();

    if (imageCapture.isRecording()) {
      color = ImVec4(0.2f, 0.7f, 0.2f, 1.0f);
    }
    ImGui::PushStyleColor(ImGuiCol_Button, color);
    if (ImGui::Button("Start recording")) {
      imageCapture.startRecording(step * 1000, duration * 1000);
    }
    ImGui::PopStyleColor();

    ImGui::EndTabItem();
  }
}
