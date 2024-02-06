#pragma once
#include "ofMain.h"
#include "glm/gtx/intersect.hpp"

class Ray {
public:
    Ray(){};
    Ray(glm::vec3 origin, glm::vec3 direction);
    void set(glm::vec3 origin, glm::vec3 direction);

    const glm::vec3 getOrigin();
    const glm::vec3  getDirection();
    bool isRayCollidingWithPrimitive(const of3dPrimitive& primitive, glm::vec2 & baricentricCoords, float &distance);
    void draw(float radius, const ofColor &color);

private:
    glm::vec3 origin;
    glm::vec3 direction;
};
