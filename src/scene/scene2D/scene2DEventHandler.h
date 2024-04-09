#pragma once
#include "scene2D.h"

class Scene2DEventHandler {
public:
  Scene2DEventHandler(Scene2D *scene2D, Cursor *cursor):
      scene2D(scene2D), cursor(cursor) {}
  ~Scene2DEventHandler();
  void activateHandler();
  void deactivateHandler();

private:
  Scene2D *scene2D;
  Cursor *cursor;
  bool isActivated = false;

  bool isMouseInScene() const;
  void mouseDragged(ofMouseEventArgs &mouseArgs);
  void mousePressed(ofMouseEventArgs &mouseArgs);
  void mouseReleased(ofMouseEventArgs &mouseArgs);
  void keyPressed(ofKeyEventArgs &keyArgs);
  void leftMouseButtonPressed();
  void leftMouseButtonReleased();
  void rightMouseButtonPressed();
};
