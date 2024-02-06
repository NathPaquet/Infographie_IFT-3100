#include "Planet.h"

void Planet::draw() const{
    ofPushStyle();
    mTex.bind();
	primitive->draw();
    mTex.unbind();
    ofPopStyle();
}

Planet::Planet(const float x, const float y, const float z){
    auto sphere = ofSpherePrimitive(20.f, 20, OF_PRIMITIVE_TRIANGLES);
    this->mainMesh = sphere.getMesh();
    // for (int side =0; side < 6; side++){
    //     box.setSideColor(side , ofColor::fromHsb(ofRandom(255), 255, 255));
    // }
    ofDisableArbTex();
    mTex.enableMipmap();
    ofLoadImage(mTex,"earth.jpg");
    
    mTex.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    this->primitive = std::make_unique<ofSpherePrimitive>(std::move(sphere));
    this->primitive->setGlobalPosition(x,y,z);
    this->position = ofVec3f(x,y,z);
}

