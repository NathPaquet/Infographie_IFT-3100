#include "ofApp.h"

#include "ImHelpers.h"
#include "constants.h"
#include "of3dUtils.h"
#include "scene/Planet.h"
#include "scene/SceneElementFactory.h"

#include <iostream>

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetWindowTitle("BasedEngine");
  ofSetLogLevel(OF_LOG_VERBOSE);
  ofDisableAlphaBlending();
  ofEnableDepthTest();
  // required call
  this->gui.setup(nullptr, true, ImGuiConfigFlags_ViewportsEnable);
  this->sceneManager = std::make_unique<SceneManager>();
  this->scene2DManager = std::make_unique<SceneManager>();
  this->currentSceneManager = this->sceneManager.get();
  this->sceneGraph = std::make_unique<SceneGraph>(this->currentSceneManager);
  this->propertiesPanel = std::make_unique<PropertiesPanel>();
  this->backgroundImage.load("background.jpg");

  ofDisableArbTex();
  this->backgroundTexture = this->backgroundImage.getTexture();
  this->backgroundTexture.enableMipmap();
  this->backgroundTexture.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  this->backgroundTexture.generateMipmap();

  this->sphere.enableTextures();
  // Initialize camera
  this->camera.setDistance(Constants::DEFAULT_CAMERA_DISTANCE);

  // Initialize light
  this->light.setAmbientColor(Constants::AMBIANT_COLOR);
  this->light.setPosition(Constants::LIGHT_POSITION);
  ofEnableSmoothing();
  ofEnableLighting();
  this->light.enable();

  this->ray = Ray();
}

//--------------------------------------------------------------
void ofApp::exit() {
  this->gui.exit();
}

glm::highp_vec3 ofApp::findMouseClick3DPosition() const {
  const glm::vec3 screenMouse(ofGetMouseX(), ofGetMouseY(), 0);
  auto &&worldMouse = camera.screenToWorld(screenMouse);
  auto &&worldMouseEnd = camera.screenToWorld(glm::vec3(screenMouse.x, screenMouse.y, 1.0f));
  auto &&worldMouseDirection = worldMouseEnd - worldMouse;
  return worldMouseDirection;
}

//--------------------------------------------------------------
void ofApp::update() {
  // ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void ofApp::draw() {
  cursor.drawCursor(ofGetMouseX(), ofGetMouseY());
  camera.begin();

  sphere.draw(); // Light representation

  currentSceneManager->drawScene();

  gui.begin();

  processMouseActions();

  camera.end();

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
    this->propertiesPanel->drawPropertiesPanel(this->currentSceneManager->getSelectedObjectReference());
    ImGui::End();
  }
}

bool ofApp::isMouseClickInScene() {
  return ofGetMouseX() > Constants::SCENE_GRAPH_WIDTH && ofGetMouseX() < ofGetWidth() - Constants::PROPERTIES_PANEL_WIDTH;
}

void ofApp::drawSceneObjectGraph() {
  ImGui::SetNextWindowPos(ImVec2(ofGetWindowPositionX(), ofGetWindowPositionY()), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(Constants::SCENE_GRAPH_WIDTH, ofGetHeight()), ImGuiCond_Always);
  if (ImGui::Begin("Scene Objects", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize)) {
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);

    if (this->cursor.getCursorMode() == CursorMode::REMOVING) {
      ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)Constants::BUTTON_CLICKED_BACKGROUND_COLOR);
      ImGui::PushStyleColor(ImGuiCol_Border, (ImVec4)Constants::BUTTON_CLICKED_BORDER_COLOR);

      if (ImGui::Button("Click on object to delete", ImVec2(ImGui::GetContentRegionAvail().x, Constants::GRAPH_SCENE_BUTTON_HEIGHT))) {
        this->cursor.setCursorMode(CursorMode::NAVIGATION);
      }
      ImGui::PopStyleColor(2);
    } else {
      if (ImGui::Button("Delete Object", ImVec2(ImGui::GetContentRegionAvail().x, Constants::GRAPH_SCENE_BUTTON_HEIGHT))) {
        this->cursor.setCursorMode(CursorMode::REMOVING);
      }
    }

    if (ImGui::Button("Delete Selection", ImVec2(ImGui::GetContentRegionAvail().x, Constants::GRAPH_SCENE_BUTTON_HEIGHT))) {
      this->currentSceneManager->removeAllSelectedObjects();
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
        currentElementToAdd = ElementType::TRIANGLE;
        this->cursor.setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Add Square")) {
        currentElementToAdd = ElementType::SQUARE;
        this->cursor.setCursorMode(CursorMode::ADDING);
      }
      if (ImGui::MenuItem("Add circle")) {
        currentElementToAdd = ElementType::CIRCLE;
        this->cursor.setCursorMode(CursorMode::ADDING);
      }
    } else {
      ImGui::SeparatorText("Automatic generation");
      if (ImGui::MenuItem("Generate Random Galaxy")) {
        generateRandomGalaxy(20);
      }
      ImGui::SeparatorText("3D object");
      if (ImGui::MenuItem("Add Sphere")) {
        currentElementToAdd = ElementType::SPHERE;
        this->cursor.setCursorMode(CursorMode::ADDING);
      }

      if (ImGui::MenuItem("Add Cube")) {
        currentElementToAdd = ElementType::CUBIC;
        this->cursor.setCursorMode(CursorMode::ADDING);
      }

      if (ImGui::MenuItem("Add Cylinder")) {
        currentElementToAdd = ElementType::CYLINDER;
        this->cursor.setCursorMode(CursorMode::ADDING);
      }

      ImGui::SeparatorText("3D model");
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
    if (ImGui::MenuItem("3D Scene")) {
      this->currentSceneManager = this->sceneManager.get();
      this->isScene2D = false;
      this->sceneGraph->setSceneManager(this->currentSceneManager);
      ofLogNotice() << "3D Scene button pressed";
    }
    if (ImGui::MenuItem("2D Scene")) {
      this->currentSceneManager = this->scene2DManager.get();
      this->sceneGraph->setSceneManager(this->currentSceneManager);
      this->isScene2D = true;

      ofLogNotice() << "2D Scene button pressed";
    }
    ImGui::EndMenu();
  }
}

void ofApp::processMouseActions() {
  if (this->shouldDragObject) {
    this->camera.disableMouseInput();
  }
  if (!isMouseClickInScene()) {
    this->camera.disableMouseInput();
    return;
  }

  auto &&maybeObject = cursor.setRayWithCollidingObject(this->currentSceneManager->getObjects(), this->camera, this->ray);
  auto &&found = maybeObject.has_value();
  const float distance = Constants::DEFAULT_DISTANCE_TO_DRAW_PRIMITIVE;
  if (!found && this->cursor.getCursorMode() == CursorMode::ADDING) {
    this->ray.drawPrimitivePreview(this->currentElementToAdd, distance);
  }

  if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
    shouldDragObject = false;
    this->camera.enableMouseInput();
  }

  if (found && std::find(this->currentSceneManager->getSelectedObject().begin(), this->currentSceneManager->getSelectedObject().end(), maybeObject.value()) != this->currentSceneManager->getSelectedObject().end()) {
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
      shouldDragObject = true;
    }

    if (ImGui::IsMouseDown(ImGuiMouseButton_Left)
        && shouldDragObject
        && this->cursor.getCursorMode() == CursorMode::NAVIGATION) {
      this->currentSceneManager->setObjectPosition(maybeObject.value(), ray.getOrigin() + ray.getDirection() * distance);
      this->camera.disableMouseInput();
    }
  }

  if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
    if (found && this->cursor.getCursorMode() == CursorMode::NAVIGATION) {
      if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftCtrl))) {
        currentSceneManager->clickSelectionSceneObject(maybeObject.value());
      } else {
        currentSceneManager->setSelectedSceneObject(maybeObject.value());
      }

    } else if (found && this->cursor.getCursorMode() == CursorMode::REMOVING) {
      currentSceneManager->removeObject(maybeObject.value()); // TODO : Ajouter une nouvelle m�thode pour supprimer un objet
      this->cursor.setCursorMode(CursorMode::NAVIGATION);

    } else if (this->cursor.getCursorMode() == CursorMode::ADDING) {
      currentSceneManager->addElement(ray, distance, this->currentElementToAdd);
      this->cursor.setCursorMode(CursorMode::NAVIGATION);
      currentSceneManager->setSelectedSceneObject(currentSceneManager->getObjects().back().get());
    }
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
    this->currentSceneManager->addElement(ray, distance, static_cast<ElementType>(intDistribution(gen)));
  }
}
