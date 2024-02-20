#pragma once

#include "./utils/ImageCapture.h"
#include "ofxImGui.h"

class ExportMenu {
public:
  void createExportMenu(bool *show);

private:
  ImVec4 color;

  ImageCapture imageCapture;
  int duration = 3;
  float step = 1;
  int numberOfImages;

  void createExportImageTabItem();
  void createExportSequenceTabItem();
};
