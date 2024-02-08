#pragma once

#include "ofxImGui.h"
#include "utils/ImageCapture.h"

class Tools {
public:
  void createToolsMenu();

private:
  ImageCapture imageCapture;
  bool showExportMenu = false;

  int duration = 3;
  float step = 1;
  int numberOfImages;
};
