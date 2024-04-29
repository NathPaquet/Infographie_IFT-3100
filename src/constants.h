#pragma once

#include "imgui.h"

namespace Constants {
  // SIZES
  constexpr float PROPERTIES_PANEL_WIDTH = 200.0f;
  constexpr float SCENE_GRAPH_WIDTH = 200.0f;
  constexpr float GRAPH_SCENE_BUTTON_HEIGHT = 30.0f;
  constexpr float DEFAULT_SIZE = 20.0f;
  constexpr float DEFAULT_SKYBOX_SIZE = 100.0f;

  // COLORS
  constexpr ImColor MENU_BAR_BACKGROUND_COLOR = ImColor(51, 56, 68, 255);
  constexpr ImColor BUTTON_CLICKED_BACKGROUND_COLOR = ImColor(102, 39, 55, 255);
  constexpr ImColor BUTTON_CLICKED_BORDER_COLOR = ImColor(209, 45, 73, 255);
  constexpr ImColor PRIMITIVE_PREVIEW_COLOR = ImColor(240, 233, 233, 255);
  const ofColor SELECTED_OBJECT_FRAME_COLOR = ofColor(255, 255, 255, 100);
  const ofColor AMBIANT_COLOR = ofColor(0, 0, 0);

  // CAMERA
  constexpr float DEFAULT_CAMERA_NEAR_CLIP = 0.1f;
  constexpr float DEFAULT_CAMERA_FAR_CLIP = 10000.0f;
  constexpr float DEFAULT_CAMERA_FOV = 60.0f;

  // DISTANCES
  constexpr float DEFAULT_DISTANCE_TO_DRAW = 200.0f;
  constexpr float DEFAULT_CAMERA_DISTANCE = 200.0f;

  // POSITION
  constexpr glm::vec3 LIGHT_POSITION = glm::vec3(0.0f, 0.0f, 0.0f);

  // MODELS PATH
  constexpr auto PLANET_EARTH_MODEL_PATH = "models/planet-earth/scene.gltf";
  constexpr auto FREDDY_PLUSH_MODEL_PATH = "models/fnaf-freddy-plush/scene.gltf";
  constexpr auto SPACE_SHIP_MODEL_PATH = "models/space-ship/scene.gltf";

  // CURSOR PATH
  constexpr auto HAND_GRAB_CURSOR_PATH = "cursors/hand-grab.svg";
  constexpr auto HAND_OPEN_CURSOR_PATH = "cursors/cursor-hand-open-svgrepo-com.svg";
  constexpr auto ERASE_CURSOR_PATH = "cursors/erase-svgrepo-com.svg";
  constexpr auto ADD_CURSOR_PATH = "cursors/add-circle-svgrepo-com.svg";

  // CONVOLUTION
  const std::array<float, 9> CONVOLUTION_BLUR = {
      1 / 9.f,
      1 / 9.f,
      1 / 9.f,
      1 / 9.f,
      1 / 9.f,
      1 / 9.f,
      1 / 9.f,
      1 / 9.f,
      1 / 9.f,
  };
  const std::array<float, 9> CONVOLUTION_SHARPEN = {
      0.f,
      -1.f,
      0.f,
      -1.f,
      5.f,
      -1.f,
      0.f,
      -1.f,
      0.f,
  };

  // OTHER
  constexpr float SCROLL_POWER = 2.f;

  // SPLINE
  constexpr int CATMULL_ROM_QUADRUPLE_SIZE = 4;
  constexpr float CATMULL_ROM_ALPHA = 0.5f;
  constexpr int CATMULL_ROM_NUM_POINTS = 100;
  constexpr float CATMULL_ROM_POINT_RADIUS = 4.0f;
  constexpr float MIN_CATMULL_ROM_ALPHA_VALUE = 0.0f;
  constexpr float MAX_CATMULL_ROM_ALPHA_VALUE = 1.0f;

  // LIGHTS
  constexpr float MIN_ATTENUATION_VALUE = 0.0f;
  constexpr float MAX_ATTENUATION_VALUE = 1.0f;

  // SKYBOX
  constexpr auto CUBEMAP_TEXTURE_SKYBOX_BLUE = "cubemaps/blue/";
  constexpr auto CUBEMAP_TEXTURE_SKYBOX_RED = "cubemaps/red/";
  constexpr auto CUBEMAP_TEXTURE_SKYBOX_LIGHTBLUE = "cubemaps/lightblue/";
}