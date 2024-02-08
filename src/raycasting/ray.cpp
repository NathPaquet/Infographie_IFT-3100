#include "Ray.h"

Ray::Ray(glm::vec3 origin, glm::vec3 direction) {
	this->origin = origin;
	this->direction = glm::normalize(direction);
}

void Ray::set(glm::vec3 origin, glm::vec3 direction) {
	this->origin = origin;
	this->direction = glm::normalize(direction);
}

const glm::vec3 Ray::getOrigin() {
	return this->origin;
}

const glm::vec3 Ray::getDirection() {
	return this->direction;
}

void Ray::draw(float radius) {
	ofPushStyle();
	// draw origin
	ofSetColor(246, 233, 101);
	// draw direction
	auto end = this->origin + (this->direction * (radius * 10.0f));
	ofDrawSphere(end, 20.f);
	ofSetLineWidth(3);
	ofDrawLine(origin, end);
	ofSetLineWidth(1);
	ofPopStyle();
}