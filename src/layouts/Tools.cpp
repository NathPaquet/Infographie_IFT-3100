#include "Tools.h"

void Tools::createToolsMenu() {
    if (ImGui::BeginMenu("Tools")) {
        if (ImGui::MenuItem("Export sequence")) {
            showExportMenu = true;
            ofLogNotice("Export sequence") << "Press!";
        }

        ImGui::EndMenu();
    }

    if (showExportMenu) {
        ImGui::Begin("Export sequence menu", &showExportMenu);

        ImGui::SliderInt("Duration (seconds)", &duration, 1, 10);
        ImGui::Separator();
        ImGui::SliderFloat("Step (seconds)", &step, 0.25f, 1.0f, "%.2f", 0.25f);
        ImGui::Separator();

        numberOfImages = duration / step;
        ImGui::Text("Number of images: %d", numberOfImages);
        ImGui::Separator();

        ImVec4 color;
        if (imageCapture.isRecording()) {
            color = ImVec4(0.2f, 0.7f, 0.2f, 1.0f);
        }
        ImGui::PushStyleColor(ImGuiCol_Button, color);
        if (ImGui::Button("Start recording")) {
            imageCapture.startRecording(step * 1000, duration * 1000);
        }
        ImGui::PopStyleColor();

        ImGui::End();
    }
}
