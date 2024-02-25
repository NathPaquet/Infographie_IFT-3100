#pragma once

#include "./export/ImageFormatDropdown.h"
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

  ImageFormatDropdown imageFormatDropdown;
  void createExportImageTabItem();
  void createExportSequenceTabItem();
};
