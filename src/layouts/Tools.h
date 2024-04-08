#pragma once

#include "./export/ExportMenu.h"
#include "ofxImGui.h"
#include "scene/scene3D/scene3D.h"

class Tools {
public:
  Tools(Scene3D *scene3D);
  void createToolsMenu();

private:
  std::unique_ptr<Scene3D> scene3D;

  ExportMenu exportMenu;
  bool showExportMenu = false;
};
