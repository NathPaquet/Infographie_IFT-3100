#include "Planet.h"

void Planet::draw() const{
    ofPushStyle();
    ofNoFill();
	ofDrawSphere(this->position.x, this->position.y, this->position.z, 20.f);
    ofPopStyle();
}

Planet::Planet(const float x, const float y, const float z){
    this->position = ofVec3f(x,y,z);
}

