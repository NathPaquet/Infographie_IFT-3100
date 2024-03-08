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

void Cursor::computeRay(const ofEasyCam &camera, Ray &ray) const {
  auto mouseWorldDirection = findMouseDirectionInWorld(camera);
  const glm::vec3 cameraPositionInScreen(ofGetMouseX(), ofGetMouseY(), 0);
  auto &&cameraPostionInWorld = camera.screenToWorld(cameraPositionInScreen);
  ray.set(cameraPostionInWorld, mouseWorldDirection);
}

glm::highp_vec3 Cursor::findMouseDirectionInWorld(const ofEasyCam &camera) const {
  const glm::vec3 screenMouse0(ofGetMouseX(), ofGetMouseY(), 0);
  const glm::vec3 screenMouse1(ofGetMouseX(), ofGetMouseY(), 1);
  auto &&worldMouse0 = camera.screenToWorld(screenMouse0);
  auto &&worldMouse1 = camera.screenToWorld(screenMouse1);
  auto &&worldMouseDirection = worldMouse1 - worldMouse0;
  return worldMouseDirection;
}

std::optional<const SceneObject *> Cursor::setRayWithCollidingObject(const std::list<std::unique_ptr<SceneObject>> &objects, const ofEasyCam &camera, Ray &ray) {
  this->computeRay(camera, ray);

  glm::vec2 baricentricCoordinates;
  float distance;
  float distanceToClosestIntersection = numeric_limits<float>::max();
  const SceneObject *foundSceneObject{nullptr};
  for (auto &&object : objects) {
    bool intersects = ray.isRayCollidingWithPrimitive(object.get()->getPrimitive(), baricentricCoordinates, distance);
    if (intersects && (distance < distanceToClosestIntersection)) {
      foundSceneObject = object.get();
      distanceToClosestIntersection = distance;
    }
  }
  return foundSceneObject ? std::optional(foundSceneObject) : std::nullopt;
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
