#pragma once

#include "ofMain.h"
#include "sceneObject.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void addElement(SceneObject & element);
	void removeElement(size_t index);
	void drawScene();

private:
	void clearScene();

	std::vector<SceneObject> sceneElements;
};

