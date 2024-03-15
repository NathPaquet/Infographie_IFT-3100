#pragma once
#include "ofMain.h"
#include "ofxSVG.h"

enum class CursorMode {
  GRABBING,
  NAVIGATION,
  CAMERA_MOVING,
  SELECTION,
  DRAWING,
  ADDING,
  REMOVING
};

class Cursor {
public:
  Cursor(CursorMode type);

  void drawCursor(float x, float y);
  void setCursorMode(CursorMode cursorType);
  CursorMode getCursorMode() const;

private:
  void drawSceneCursor(float x, float y);
  bool isCursorInScene() const;
  // GLFWCursor *mapCursorTypeToGLFWCursor(CursorMode cursorType);
  CursorMode mode;
  ofxSVG cursorSVG;

  GLFWwindow *window = static_cast<ofAppGLFWWindow *>(ofGetWindowPtr())->getGLFWWindow();
};