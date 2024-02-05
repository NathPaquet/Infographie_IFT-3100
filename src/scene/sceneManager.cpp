#include "sceneManager.h"

SceneManager::SceneManager()
{
	ofLogNotice("SceneManager") << "SceneManager constructor";
}

SceneManager::~SceneManager() {
	clearScene();
}

void SceneManager::addElement(SceneObject& element)
{
	sceneElements.push_back(std::move(element));
}

void SceneManager::removeElement(size_t index) {
	if (index < 0 || index >= sceneElements.size()) {
		return;
	}
	sceneElements.erase(std::next(sceneElements.begin(), index));
}

void SceneManager::drawScene() {
	for (auto&& element : sceneElements) {
		element.draw();
	}
}

void SceneManager::clearScene() {
	sceneElements.clear();
}
