#pragma once

#include "./export/ExportMenu.h"
#include "ofxImGui.h"
#include "scene/scene3D/scene3D.h"

class Tools {
public:
  void createToolsMenu(Scene3D *scene3D);

private:
  ExportMenu exportMenu;
  bool showExportMenu = false;
};
