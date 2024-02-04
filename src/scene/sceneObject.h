#pragma once

#include "ofMain.h"

class SceneObject
{
public:
	ofVec3f position;
	ofColor color;

	virtual void draw() const;
};
