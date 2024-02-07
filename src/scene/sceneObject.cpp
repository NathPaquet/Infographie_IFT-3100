#include "sceneObject.h"

void SceneObject::draw() const {
	ofLogNotice() << "SceneObject::draw()";
}

void SceneObject::draw_properties() {
}

const of3dPrimitive &SceneObject::getPrimitive() const {
    return *this->primitive.get();
}
