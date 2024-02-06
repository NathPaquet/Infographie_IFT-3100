#pragma once

#include "sceneObject.h"

class Planet : public SceneObject{
    public :
        void draw() const override;
        Planet(const float x, const float y, const float z);
    private :
        std::unique_ptr<of3dPrimitive> primitive;
        ofMesh mainMesh;
        ofTexture mTex;
};
