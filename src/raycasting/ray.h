#pragma once
#include "ofMain.h"


class Ray {
public:
    Ray(){};
    Ray(glm::vec3 origin, glm::vec3 direction);
    void set(glm::vec3 origin, glm::vec3 direction);

    const glm::vec3 getOrigin();
    const glm::vec3  getDirection();
    void draw(float radius = 20.);

private:
    glm::vec3 origin;
    glm::vec3 direction;
};
