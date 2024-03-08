#include "Cursor.h"

#include "ofxGui.h"

Cursor::Cursor(CursorMode cursorType):
    mode(cursorType) {
}

void Cursor::drawCursor(float x, float y) {
  // cout << (mode == CursorMode::NAVIGATION ? "CursorMode::NAVIGATION" : "other") << endl;

  ImGui::SetMouseCursor(ImGuiMouseCursor_None);
  switch (mode) {
    case CursorMode::SELECTION:
      // ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
      drawSelectionCursor(x, y);
      break;
    case CursorMode::ADDING:
      // ImGui::SetMouseCursor(ImGuiMouseCursor_TextInput);
      drawNavigationCursor(x, y);
      break;
    case CursorMode::NAVIGATION:
      drawNavigationCursor(x, y);
      break;
    case CursorMode::DRAWING:
      // ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNWSE); // GLFW_CROSSHAIR_CURSOR
      drawDrawingCursor(x, y);
      break;
    case CursorMode::REMOVING:
      // ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
      drawDrawingCursor(x, y);
      break;
    default:
      // ImGui::SetMouseCursor(ImGuiMouseCursor_None); // GLFW_ARROW_CURSOR
      break;
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

void Cursor::drawNavigationCursor(float x, float y) {
}

void Cursor::drawSelectionCursor(float x, float y) {
  ofPushMatrix();

  ofPushStyle();

  ofTranslate(x - cursorSVG.getWidth() / 2, y - cursorSVG.getHeight() / 2);
  cursorSVG.draw();

  ofPopMatrix();
  ofPopStyle();
}

void Cursor::drawDrawingCursor(float x, float y) {
  ofPushStyle();
  // paramètres de dessin
  float length = 10.0f;
  float offset = 5.0f;

  // épaisseur du trait
  ofSetLineWidth(2);

  ofSetColor(0, 0, 0);

  // dessiner la forme vectorielle
  ofDrawLine(x + offset, y, x + offset + length, y);
  ofDrawLine(x - offset, y, x - offset - length, y);
  ofDrawLine(x, y + offset, x, y + offset + length);
  ofDrawLine(x, y - offset, x, y - offset - length);
  ofPopStyle();
}

void Cursor::setCursorMode(CursorMode type) {
  this->mode = type;

  switch (mode) {
    case CursorMode::SELECTION:
      break;
    case CursorMode::ADDING:
      break;
    case CursorMode::NAVIGATION:
      cursorSVG.load("cursors/hand-grab.svg");
      break;
    case CursorMode::DRAWING:
      break;
    case CursorMode::REMOVING:
      break;
    default:
      break;
  }
}

CursorMode Cursor::getCursorMode() const {
  return this->mode;
}
