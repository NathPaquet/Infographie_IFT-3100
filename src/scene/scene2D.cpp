#include "scene2D.h"

void Scene2D::setup() {
}

void Scene2D::drawScene() {
  this->cursor->drawCursor(ofGetMouseX(), ofGetMouseY());

  ofSetColor(ofColor::red);
  ofDrawArrow(glm::vec3(0, 0, 0), glm::vec3(100, 100, 0), 1);
  ofSetColor(ofColor::green);
  ofDrawArrow(glm::vec3(0, 0, 0), glm::vec3(0, 100, 0), 1);
  ofSetColor(ofColor::white);
  ofFill();
  ofDrawCircle(0, 0, 1000);

  this->sceneManager.get()->drawScene();
}
