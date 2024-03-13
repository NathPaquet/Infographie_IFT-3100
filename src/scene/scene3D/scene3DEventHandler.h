#pragma once
#include "scene3D.h"

class Scene3DEventHandler {
public:
  Scene3DEventHandler(Scene3D *scene3D, Cursor *cursor):
      scene3D(scene3D), cursor(cursor) {}
  ~Scene3DEventHandler();
  void activateHandler();
  void deactivateHandler();

private:
  Scene3D *scene3D;
  Cursor *cursor;
  bool isActivated = false;

  bool isMouseInScene() const;
  void mouseMoved(ofMouseEventArgs &mouseArgs);
  void mouseDragged(ofMouseEventArgs &mouseArgs);
  void mousePressed(ofMouseEventArgs &mouseArgs);
  void mouseReleased(ofMouseEventArgs &mouseArgs);
  void leftMouseButtonPressed();
  void leftMouseButtonReleased();
};
