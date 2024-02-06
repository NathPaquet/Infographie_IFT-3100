#include "sceneObject.h"

void SceneObject::draw() const {
	ofLogNotice() << "SceneObject::draw()";
}

const of3dPrimitive &SceneObject::getPrimitive() const{
    return *this->primitive.get();
}
