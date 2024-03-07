#include "Cursor.h"

#include "ofxGui.h"

Cursor::Cursor(CursorMode cursorType):
    mode(cursorType) {
}

void Cursor::drawCursor(float x, float y) {
  switch (mode) {
    case CursorMode::SELECTION:
      drawSelectionCursor(x, y);
      break;
    case CursorMode::ADDING:
      drawNavigationCursor(x, y);
      break;
    case CursorMode::NAVIGATION:
      drawNavigationCursor(x, y);
      break;
    case CursorMode::DRAWING:
      drawDrawingCursor(x, y);
      break;
    default:
      break;
  }
}

glm::highp_vec3 Cursor::findMouseClick3DPosition(const ofEasyCam &camera) const {
  const glm::vec3 screenMouse(ofGetMouseX(), ofGetMouseY(), 0);
  auto &&worldMouse = camera.screenToWorld(screenMouse);
  auto &&cameraPosition = camera.getGlobalPosition();
  auto &&worldMouseDirection = worldMouse - cameraPosition;
  return worldMouseDirection;
}

std::optional<const SceneObject *> Cursor::setRayWithCollidingObject(const std::list<std::unique_ptr<SceneObject>> &objects, const ofEasyCam &camera, Ray &ray) {
  auto worldMouseDirection = findMouseClick3DPosition(camera);
  ray.set(camera.getGlobalPosition(), worldMouseDirection);

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
}

CursorMode Cursor::getCursorMode() const {
  return this->mode;
}
