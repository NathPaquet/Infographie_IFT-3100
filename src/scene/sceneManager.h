#pragma once

#include "ofMain.h"
#include "sceneObject.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void addElement(const ofVec3f &position);
	void removeElement(size_t index);
	void drawScene();
	const std::vector<std::unique_ptr<SceneObject>> &getObjects() const;

private:
	void clearScene();

	std::vector<std::unique_ptr<SceneObject>> sceneElements;
};

