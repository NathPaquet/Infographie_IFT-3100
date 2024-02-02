#pragma once
#include "ofMain.h"
#include "sceneObject.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void addElement(SceneObject* element);
	void removeElement(int index);
	void drawScene();

private:
	void clearScene();

	std::vector<SceneObject*> sceneElements;
};

