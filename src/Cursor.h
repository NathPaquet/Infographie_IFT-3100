#pragma once
#include "object/sceneObject.h"
#include "ofxSVG.h"
#include "ray.h"

#include <optional>

enum class CursorMode {
  NAVIGATION,
  SELECTION,
  DRAWING,
  ADDING,
  REMOVING
};

class Cursor {
public:
  Cursor(CursorMode type);

  void drawCursor(float x, float y);
  void computeRay(const ofEasyCam &camera, Ray &ray) const;

  std::optional<const SceneObject *> setRayWithCollidingObject(const std::list<std::unique_ptr<SceneObject>> &objects, const ofEasyCam &camera, Ray &ray);
  glm::highp_vec3 findMouseDirectionInWorld(const ofEasyCam &camera) const;
  void setCursorMode(CursorMode cursorType);
  CursorMode getCursorMode() const;

private:
  void drawNavigationCursor(float x, float y);
  void drawSelectionCursor(float x, float y);
  void drawDrawingCursor(float x, float y);
  // GLFWCursor *mapCursorTypeToGLFWCursor(CursorMode cursorType);
  CursorMode mode;
  ofxSVG cursorSVG;

  GLFWwindow *window = static_cast<ofAppGLFWWindow *>(ofGetWindowPtr())->getGLFWWindow();
};