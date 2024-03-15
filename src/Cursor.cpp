#include "Cursor.h"

#include "constants.h"
#include "ofxGui.h"

Cursor::Cursor(CursorMode cursorType) {
  this->setCursorMode(cursorType);
}

void Cursor::drawCursor(float x, float y) {
  if (!isCursorInScene()) {
    if (ImGui::IsAnyItemHovered()) {
      ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
    } else {
      ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
    }
  } else {
    ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    this->drawSceneCursor(x, y);
  }
}

void Cursor::drawSceneCursor(float x, float y) {
  ofPushMatrix();

  ofPushStyle();

  ofTranslate(x - cursorSVG.getWidth() / 2, y - cursorSVG.getHeight() / 2);
  cursorSVG.draw();

  ofPopMatrix();
  ofPopStyle();
}

bool Cursor::isCursorInScene() const {
  return !ImGui::GetIO().WantCaptureMouse;
}

void Cursor::setCursorMode(CursorMode type) {
  this->mode = type;

  switch (mode) {
    case CursorMode::SELECTION:
      // TODO : Change cursor
      cursorSVG.load(Constants::HAND_GRAB_CURSOR_PATH);
      break;
    case CursorMode::GRABBING:
      cursorSVG.load(Constants::HAND_GRAB_CURSOR_PATH);
      break;
    case CursorMode::CAMERA_MOVING:
      // TODO : Change cursor
      cursorSVG.load(Constants::HAND_GRAB_CURSOR_PATH);
      break;
    case CursorMode::ADDING:
      cursorSVG.load(Constants::ADD_CURSOR_PATH);
      break;
    case CursorMode::NAVIGATION:
      cursorSVG.load(Constants::HAND_OPEN_CURSOR_PATH);
      break;
    case CursorMode::DRAWING:
      break;
    case CursorMode::REMOVING:
      cursorSVG.load(Constants::ERASE_CURSOR_PATH);
      break;
    default:
      break;
  }
}

CursorMode Cursor::getCursorMode() const {
  return this->mode;
}
