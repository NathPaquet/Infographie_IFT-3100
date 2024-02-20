#pragma once

#include "./export/ExportMenu.h"
#include "ofxImGui.h"

class Tools {
public:
  void createToolsMenu();

private:
  ExportMenu exportMenu;
  bool showExportMenu = false;
};
