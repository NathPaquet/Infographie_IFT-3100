#pragma once

#include "ofMain.h"

class SceneObject
{
public:
	ofVec3f position;
	ofColor color;

	virtual void draw() const;
	const of3dPrimitive &getPrimitive() const;
protected:
	std::unique_ptr<of3dPrimitive> primitive;

};
