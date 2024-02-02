#include "sceneManager.h"

SceneManager::SceneManager()
{
	ofLogNotice("SceneManager") << "SceneManager constructor";
}

SceneManager::~SceneManager() {
    clearScene();
}

void SceneManager::addElement(SceneObject* element)
{
    sceneElements.push_back(element);
}

void SceneManager::removeElement(int index) {
    if (index >= 0 && index < sceneElements.size()) {
        delete sceneElements[index];
        sceneElements.erase(sceneElements.begin() + index);
    }
}

void SceneManager::drawScene() {
    for (const auto& element : sceneElements) {
        ofLogNotice("SceneManager") << "Drawing element ";
    }
}

void SceneManager::clearScene() {
    for (auto& element : sceneElements) {
        delete element;
    }
    sceneElements.clear();
}