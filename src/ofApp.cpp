#include "ofApp.h"

#include "ImHelpers.h"
#include "constants.h"
#include "of3dUtils.h"
#include "scene/object/object3D/Planet.h"
#include "scene/object/sceneObjectFactory.h"

#include <iostream>

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetWindowTitle("BasedEngine");
  ofSetLogLevel(OF_LOG_VERBOSE);
  ofDisableAlphaBlending();
  ofEnableDepthTest();
  // required call

  this->cursor = std::make_unique<Cursor>(CursorMode::NAVIGATION);

  // Setup 3D scene
  this->scene3D = std::make_unique<Scene3D>(std::make_unique<SceneManager>(), cursor.get());
  this->scene3D->setup();

  // Setup 2D scene
  this->scene2D = std::make_unique<Scene2D>(std::make_unique<SceneManager>(), cursor.get());
  this->scene2D->setup();

  // Setup initial scene
  this->currentScene = this->scene3D.get();

  this->gui.setup(nullptr, true, ImGuiConfigFlags_ViewportsEnable);
  this->sceneGraph = std::make_unique<SceneGraph>(this->currentScene->getSceneManager());
  this->propertiesPanel = std::make_unique<PropertiesPanel>();

  ofDisableArbTex();
  this->backgroundTexture = this->backgroundImage.getTexture();
  this->backgroundTexture.enableMipmap();
  this->backgroundTexture.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  this->backgroundTexture.generateMipmap();
}

//--------------------------------------------------------------
void ofApp::exit() {
  this->gui.exit();
}

//--------------------------------------------------------------
void ofApp::draw() {
  this->currentScene->drawScene();

  gui.begin();

  // Draw properties panel menu
  drawPropertiesPanel();

  // Draw scene element menu
  drawSceneObjectGraph();

  // Draw scene top menu
  drawSceneTopMenu();
  gui.end();
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
      if (ImGui::MenuItem("Add Triangle")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::TRIANGLE);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Add Square")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::SQUARE);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Add Circle")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::CIRCLE);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Add Star")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::STAR);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Add Line")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::LINE);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
    } else {
      ImGui::SeparatorText("Automatic generation");
      if (ImGui::MenuItem("Generate Random Galaxy")) {
        generateRandomGalaxy(20);
      }
      ImGui::SeparatorText("3D object");
      if (ImGui::MenuItem("Add Sphere")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::SPHERE);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }

      if (ImGui::MenuItem("Add Cube")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::CUBIC);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }

      if (ImGui::MenuItem("Add Cylinder")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::CYLINDER);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }

      ImGui::SeparatorText("3D model");

      if (ImGui::MenuItem("Planet earth")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::PLANET_EARTH);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Freddy plush")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::FREDDY_PLUSH);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Space ship")) {
        this->currentScene->setCurrentObjectToAdd(ElementType::SPACE_SHIP);
        this->cursor.get()->setCursorMode(CursorMode::ADDING);
      }
    }
    ImGui::EndMenu();
  }
}

void ofApp::drawSceneTopMenu() {
  ImGui::SetNextWindowPos(ImVec2(ofGetWindowPositionX() + Constants::SCENE_GRAPH_WIDTH, ofGetWindowPositionY()), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(ofGetWidth() - (Constants::SCENE_GRAPH_WIDTH + Constants::PROPERTIES_PANEL_WIDTH), ofGetHeight()), ImGuiCond_Always);

  ImGui::PushStyleColor(ImGuiCol_MenuBarBg, (ImVec4)Constants::MENU_BAR_BACKGROUND_COLOR);

  if (ImGui::Begin("Menu bar", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize)) {
    if (ImGui::BeginMenuBar()) {
      this->drawSceneObjectGraphCreationMenu();
      this->createViewMenu();
      tools.createToolsMenu();

      ImGui::EndMenuBar();
    }
    ImGui::End();
  }

  ImGui::PopStyleColor();
}

void ofApp::createViewMenu() {
  if (ImGui::BeginMenu("View")) {
    if (this->isScene2D && ImGui::MenuItem("Display 3D Scene")) {
      this->currentScene = this->scene3D.get();
      this->isScene2D = false;
      this->sceneGraph->setSceneManager(this->currentScene->getSceneManager());
    }
    if (!this->isScene2D && ImGui::MenuItem("Display 2D Scene")) {
      this->currentScene = this->scene2D.get();
      this->isScene2D = true;
      this->sceneGraph->setSceneManager(this->currentScene->getSceneManager());
      ofLogNotice() << "2D Scene button pressed";
    }
    if (this->isScene2D) {
      ImGui::SeparatorText("2D scene options");
    } else {
      ImGui::SeparatorText("3D scene options");
      if (ImGui::MenuItem((this->isBoundingBoxEnabled ? "Disable bounding box" : "Enable bounding box"))) {
        this->isBoundingBoxEnabled = !this->isBoundingBoxEnabled;
        this->currentScene->getSceneManager()->toggleActivationBoundingBox();
      }
    }
    ImGui::EndMenu();
  }
}

void ofApp::generateRandomGalaxy(int nbElements) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(-500, 500);
  std::uniform_int_distribution intDistribution(0, 2);

  for (int i = 0; i < nbElements; i++) {
    Ray ray;
    glm::vec3 randomPosition;
    randomPosition.x = dis(gen);
    randomPosition.y = dis(gen);
    randomPosition.z = dis(gen);
    auto distance = glm::length(randomPosition);
    ray.set({0, 0, 0}, randomPosition);
    // TODO : Add a new method in scene object ?
    this->currentScene->getSceneManager()->addElement(ray.getOrigin() + ray.getDirection() * distance, static_cast<ElementType>(intDistribution(gen)));
  }
}
