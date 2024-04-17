#include "ofApp.h"

#include "ImHelpers.h"
#include "constants.h"
#include "of3dUtils.h"
#include "scene/object/object3D/primitive/Planet.h"
#include "scene/object/sceneObjectFactory.h"
#include "utils/loadingScreen.h"

#include <iostream>
#include <textures/TextureRepository.h>

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetWindowTitle("BasedEngine");
  ofSetLogLevel(OF_LOG_VERBOSE);
  ofDisableAlphaBlending();
  ofEnableDepthTest();
  ofSetVerticalSync(true);
  ofDisableArbTex();
  // required call

  this->cursor = std::make_unique<Cursor>(CursorMode::NAVIGATION);

  // Setup 3D scene
  this->scene3D = std::make_unique<Scene3D>(std::make_unique<SceneManager>());
  this->scene3DEventHandler = std::make_unique<Scene3DEventHandler>(this->scene3D.get(), this->cursor.get());
  this->scene3D->setup();

  // Setup 2D scene
  this->scene2D = std::make_unique<Scene2D>(std::make_unique<SceneManager>());
  this->scene2DEventHandler = std::make_unique<Scene2DEventHandler>(this->scene2D.get(), this->cursor.get());
  this->scene2D->setup();

  // Setup initial scene
  this->currentScene = this->scene3D.get();
  this->scene3DEventHandler.get()->activateHandler();

  this->gui.setup(nullptr, true, ImGuiConfigFlags_ViewportsEnable);
  this->sceneGraph = std::make_unique<SceneGraph>(this->currentScene->getSceneManager());
  this->windowCamera = std::make_unique<WindowCamera>(this->scene3D.get());
  this->cameraPanel = std::make_unique<CameraPanel>(this->currentScene->getSceneManager(), windowCamera.get());
  this->propertiesPanel = std::make_unique<PropertiesPanel>();

  ofBackground(0);
  this->backgroundTexture = this->backgroundImage.getTexture();
  this->backgroundTexture.enableMipmap();
  this->backgroundTexture.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  this->backgroundTexture.generateMipmap();

  loadDefaultTextures();
}

//--------------------------------------------------------------
void ofApp::exit() {
  this->gui.exit();
}

//--------------------------------------------------------------
void ofApp::draw() {
  gui.begin();

  this->currentScene->drawScene();

  windowCamera->drawScene();

  this->cursor->drawCursor(ofGetMouseX(), ofGetMouseY());

  updateKeyboardShortcuts();

  // Draw properties panel menu
  drawPropertiesPanel();

  // Draw scene element menu
  drawSceneObjectGraph();

  // Draw scene top menu
  drawSceneTopMenu();

  gui.end();
}

void ofApp::update() {
  this->currentScene->update();
}

void ofApp::drawPropertiesPanel() {
  ImGui::SetNextWindowPos(ImVec2(ofGetWindowPositionX() + ofGetWidth() - Constants::PROPERTIES_PANEL_WIDTH, ofGetWindowPositionY()), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(Constants::PROPERTIES_PANEL_WIDTH, ofGetHeight()), ImGuiCond_Always);
  if (ImGui::Begin("PropertiesPanel", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize)) {
    this->propertiesPanel->drawPropertiesPanel(this->currentScene->getSelectedObjectsReference());
    ImGui::End();
  }
}

void ofApp::drawSceneObjectGraph() {
  ImGui::SetNextWindowPos(ImVec2(ofGetWindowPositionX(), ofGetWindowPositionY()), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(Constants::SCENE_GRAPH_WIDTH, ofGetHeight()), ImGuiCond_Always);
  if (ImGui::Begin("Scene Objects", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize)) {
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);

    if (this->cursor.get()->getCursorMode() == CursorMode::REMOVING) {
      ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)Constants::BUTTON_CLICKED_BACKGROUND_COLOR);
      ImGui::PushStyleColor(ImGuiCol_Border, (ImVec4)Constants::BUTTON_CLICKED_BORDER_COLOR);

      if (ImGui::Button("Click on object to delete", ImVec2(ImGui::GetContentRegionAvail().x, Constants::GRAPH_SCENE_BUTTON_HEIGHT))) {
        this->cursor.get()->setCursorMode(CursorMode::NAVIGATION);
      }
      ImGui::PopStyleColor(2);
    } else {
      if (ImGui::Button("Delete Object", ImVec2(ImGui::GetContentRegionAvail().x, Constants::GRAPH_SCENE_BUTTON_HEIGHT))) {
        this->cursor.get()->setCursorMode(CursorMode::REMOVING);
      }
    }

    if (ImGui::Button("Delete Selection", ImVec2(ImGui::GetContentRegionAvail().x, Constants::GRAPH_SCENE_BUTTON_HEIGHT))) {
      this->currentScene->removeAllSelectedObjects();
    }
    ImGui::PopStyleVar(2);

    this->sceneGraph->drawSceneGraphElements();

    ImGui::End();
  }
}

void ofApp::drawSceneObjectGraphCreationMenu() {
  if (ImGui::BeginMenu("Add object")) {
    if (this->isScene2D) {
      ImGui::SeparatorText("2D object");
      if (ImGui::MenuItem("Add Triangle", "Shift+1")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::TRIANGLE);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Add Square", "Shift+2")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::SQUARE);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Add Circle", "Shift+3")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::CIRCLE);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Add Star", "Shift+5")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::STAR);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Add Line", "Shift+4")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::LINE);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Add Catmull Rom Spline", "Shift+8")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::CATMULL_ROM_SPLINE);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Add Space Rocket", "Shift+6")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::SPACE_ROCKET);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Add Magic Sword", "Shift+7")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::MAGIC_SWORD);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
    } else {
      ImGui::SeparatorText("Automatic generation");
      if (ImGui::MenuItem("Generate Random Galaxy", "Shift+=")) {
        generateRandomGalaxy(20);
      }
      ImGui::SeparatorText("3D object");
      if (ImGui::MenuItem("Add Sphere", "Shift+1")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::SPHERE);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }

      if (ImGui::MenuItem("Add Cube", "Shift+2")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::CUBIC);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }

      if (ImGui::MenuItem("Add Cylinder", "Shift+3")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::CYLINDER);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }

      ImGui::SeparatorText("Lights");

      if (ImGui::MenuItem("Add Point Light", "TODO")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::POINT_LIGHT);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Add Directional Light", "TODO")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::DIRECTIONAL_LIGHT);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Add Spot Light", "TODO")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::SPOT_LIGHT);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }

      ImGui::SeparatorText("3D model");

      if (ImGui::MenuItem("Planet earth", "Shift+4")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::PLANET_EARTH);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Freddy plush", "Shift+5")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::FREDDY_PLUSH);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Space ship", "Shift+6")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::SPACE_SHIP);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }

      ImGui::SeparatorText("Camera");
      if (ImGui::MenuItem("Add Camera", "Shift+7")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::CAMERA);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
    }
    ImGui::EndMenu();
  }
}

void ofApp::drawSceneTopMenu() {
  ImGui::SetNextWindowPos(ImVec2(ofGetWindowPositionX() + Constants::SCENE_GRAPH_WIDTH, ofGetWindowPositionY()), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(ofGetWidth() - (Constants::SCENE_GRAPH_WIDTH + Constants::PROPERTIES_PANEL_WIDTH), 0.0f), ImGuiCond_Always);

  ImGui::PushStyleColor(ImGuiCol_MenuBarBg, (ImVec4)Constants::MENU_BAR_BACKGROUND_COLOR);

  if (ImGui::Begin("Menu bar", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize)) {
    if (ImGui::BeginMenuBar()) {
      this->drawSceneObjectGraphCreationMenu();
      this->createViewMenu();
      if (!this->isScene2D && this->isSkyboxEnabled) {
        this->createSkyboxTopMenu();
      }
      tools.createToolsMenu(this->scene3D.get());
      cameraPanel.get()->create();

      ImGui::EndMenuBar();
    }
    ImGui::End();
  }

  ImGui::PopStyleColor();
}

void ofApp::createViewMenu() {
  if (ImGui::BeginMenu("View")) {
    if (ImGui::MenuItem(this->isScene2D ? "Display 3D Scene" : "Display 2D Scene", "Tab")) {
      switchBetweenScenes();
    }
    if (this->isScene2D) {
      ImGui::SeparatorText("2D scene options");
    } else {
      ImGui::SeparatorText("3D scene options");
      if (ImGui::MenuItem((this->isViewOrtho ? "Enable perspective projection" : "Enable orthographic projection"), "Alt+p")) {
        switchBetweenProjections();
      }
      if (ImGui::MenuItem((this->isSkyboxEnabled ? "Disable skybox" : "Enable skybox"), "Alt+s")) {
        toggleSkyboxFor3DScene();
      }
    }

    if (ImGui::MenuItem((this->isBoundingBoxEnabled ? "Disable bounding box" : "Enable bounding box"), "Alt+b")) {
      this->isBoundingBoxEnabled = !this->isBoundingBoxEnabled;
      this->currentScene->getSceneManager()->toggleActivationBoundingBox();
    }

    if (ImGui::MenuItem((this->isObjectAxisEnabled ? "Disable object axis" : "Enable object axis"), "Alt+a")) {
      this->isObjectAxisEnabled = !this->isObjectAxisEnabled;
      this->currentScene->getSceneManager()->toggleActivationObjectAxis();
    }

    ImGui::EndMenu();
  }
}

void ofApp::toggleSkyboxFor3DScene() {
  this->isSkyboxEnabled = !this->isSkyboxEnabled;
  this->scene3D.get()->toggleSkyboxActivation();
}

void ofApp::loadDefaultTextures() {
  shader = std::make_shared<ofShader>();
  shader->load("shaders/texture");

  TextureRepository::addTexture("Snow_03");
  TextureRepository::configureTextureWithShader("Snow_03", shader);
  TextureRepository::addTexture("Square_floor");
  TextureRepository::configureTextureWithShader("Square_floor", shader);
  TextureRepository::addTexture("Mud_cracked_dry_03");
  TextureRepository::configureTextureWithShader("Mud_cracked_dry_03", shader);
}

void ofApp::createSkyboxTopMenu() {
  if (ImGui::BeginMenu("Skybox")) {
    static int selected = 0;
    ImGui::SeparatorText("Skybox options");
    if (ImGui::Selectable("Light blue galaxy", selected == 0)) {
      selected = 0;
      this->scene3D.get()->loadSkybox(Constants::CUBEMAP_TEXTURE_SKYBOX_LIGHTBLUE);
    }
    if (ImGui::Selectable("Blue galaxy", selected == 1)) {
      selected = 1;
      this->scene3D.get()->loadSkybox(Constants::CUBEMAP_TEXTURE_SKYBOX_BLUE);
    }
    if (ImGui::Selectable("Red galaxy", selected == 2)) {
      selected = 2;
      this->scene3D.get()->loadSkybox(Constants::CUBEMAP_TEXTURE_SKYBOX_RED);
    }
    ImGui::EndMenu();
  }
}

void ofApp::updateKeyboardShortcuts() {
  if (ImGui::IsKeyPressed(ImGuiKey_Tab)) {
    switchBetweenScenes();
  }
  if (ImGui::IsKeyDown(ImGuiKey_LeftAlt)) {
    if (ImGui::IsKeyPressed(ImGuiKey_A)) {
      this->isObjectAxisEnabled = !this->isObjectAxisEnabled;
      this->currentScene->getSceneManager()->toggleActivationObjectAxis();
    }
    if (ImGui::IsKeyPressed(ImGuiKey_B)) {
      this->isBoundingBoxEnabled = !this->isBoundingBoxEnabled;
      this->currentScene->getSceneManager()->toggleActivationBoundingBox();
    }
    if (ImGui::IsKeyPressed(ImGuiKey_S) && this->currentScene == this->scene3D.get()) {
      this->isSkyboxEnabled = !this->isSkyboxEnabled;
      this->scene3D.get()->toggleSkyboxActivation();
    }
    if (ImGui::IsKeyPressed(ImGuiKey_P)) {
      switchBetweenProjections();
    }
  }
  if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) {
    if (this->isScene2D) {
      if (ImGui::IsKeyPressed(ImGuiKey_1)) {
        this->currentScene->setCurrentObjectToAdd(ElementType::TRIANGLE);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      } else if (ImGui::IsKeyPressed(ImGuiKey_2)) {
        this->currentScene->setCurrentObjectToAdd(ElementType::SQUARE);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      } else if (ImGui::IsKeyPressed(ImGuiKey_3)) {
        this->currentScene->setCurrentObjectToAdd(ElementType::CIRCLE);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      } else if (ImGui::IsKeyPressed(ImGuiKey_4)) {
        this->currentScene->setCurrentObjectToAdd(ElementType::LINE);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      } else if (ImGui::IsKeyPressed(ImGuiKey_5)) {
        this->currentScene->setCurrentObjectToAdd(ElementType::STAR);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      } else if (ImGui::IsKeyPressed(ImGuiKey_6)) {
        this->currentScene->setCurrentObjectToAdd(ElementType::SPACE_ROCKET);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      } else if (ImGui::IsKeyPressed(ImGuiKey_7)) {
        this->currentScene->setCurrentObjectToAdd(ElementType::MAGIC_SWORD);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      } else if (ImGui::IsKeyPressed(ImGuiKey_8)) {
        this->currentScene->setCurrentObjectToAdd(ElementType::CATMULL_ROM_SPLINE);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
    } else {
      if (ImGui::IsKeyPressed(ImGuiKey_1)) {
        this->currentScene->setCurrentObjectToAdd(ElementType::SPHERE);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      } else if (ImGui::IsKeyPressed(ImGuiKey_2)) {
        this->currentScene->setCurrentObjectToAdd(ElementType::CUBIC);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      } else if (ImGui::IsKeyPressed(ImGuiKey_3)) {
        this->currentScene->setCurrentObjectToAdd(ElementType::CYLINDER);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      } else if (ImGui::IsKeyPressed(ImGuiKey_4)) {
        this->currentScene->setCurrentObjectToAdd(ElementType::PLANET_EARTH);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      } else if (ImGui::IsKeyPressed(ImGuiKey_5)) {
        this->currentScene->setCurrentObjectToAdd(ElementType::FREDDY_PLUSH);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      } else if (ImGui::IsKeyPressed(ImGuiKey_6)) {
        this->currentScene->setCurrentObjectToAdd(ElementType::SPACE_SHIP);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      } else if (ImGui::IsKeyPressed(ImGuiKey_7)) {
        this->currentScene->setCurrentObjectToAdd(ElementType::CAMERA);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      } else if (ImGui::IsKeyPressed(ImGuiKey_Equal)) {
        generateRandomGalaxy(20);
      }
    }
  } else {
    if (ImGui::IsKeyPressed(ImGuiKey_C)) {
      windowCamera->switchIsShown();
    }
  }
}

void ofApp::generateRandomGalaxy(int nbElements) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(-500, 500);
  std::uniform_int_distribution intDistribution(0, 2);

  for (int i = 0; i < nbElements; i++) {
    glm::vec3 randomPosition;
    randomPosition.x = dis(gen);
    randomPosition.y = dis(gen);
    randomPosition.z = dis(gen);
    this->currentScene->getSceneManager()->addElement(randomPosition, static_cast<ElementType>(intDistribution(gen)));
  }
}

void ofApp::switchBetweenScenes() {
  if (this->isScene2D) {
    this->scene2DEventHandler.get()->deactivateHandler();
    this->scene3DEventHandler.get()->activateHandler();
    this->currentScene = this->scene3D.get();
    this->isScene2D = false;
    this->sceneGraph->setSceneManager(this->currentScene->getSceneManager());
    this->cameraPanel->setSceneManager(this->currentScene->getSceneManager());
  } else if (!this->isScene2D) {
    this->scene3DEventHandler.get()->deactivateHandler();
    this->scene2DEventHandler.get()->activateHandler();
    this->currentScene = this->scene2D.get();
    this->isScene2D = true;
    this->sceneGraph->setSceneManager(this->currentScene->getSceneManager());
    this->cameraPanel->setSceneManager(this->currentScene->getSceneManager());
  }
  this->cursor.get()->setCursorMode(CursorMode::NAVIGATION);
}

void ofApp::switchBetweenProjections() {
  this->isViewOrtho = !this->isViewOrtho;
  assert(this->currentScene != nullptr && this->currentScene == this->scene3D.get());
  this->scene3D.get()->toggleProjectionMode();
}
