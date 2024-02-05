#include "Planet.h"

void Planet::draw() const {
	ofNoFill();
	ofDrawSphere(this->position.x, this->position.y, this->position.z, 64);
}

Planet::Planet(const float x, const float y, const float z) {
	this->position = ofVec3f(x, y, z);
}
