#include "sceneObject.h"

#include "ImageImporter.h"

void SceneObject::draw(bool isSelected) const {
  ofPushStyle();
  if (isSelected) {
    ofColor complementaryColor(255 - this->color.r, 255 - this->color.g, 255 - this->color.b);
    ofSetColor(complementaryColor);
    primitive->drawWireframe();
  }

  if (mTex.isAllocated()) {
    this->mTex.bind();
    ofSetColor(this->color);
    primitive->draw();
    this->mTex.unbind();
  } else {
    ofSetColor(this->color);
    primitive->draw();
  }
  ofPopStyle();
}

void SceneObject::draw_properties() {
  if (ImGui::Button("Import image", ImVec2(100.f, 30.f))) {
    ImageImporter::importImage(this->image);
    if (this->image.isAllocated()) {
      this->mTex = image.getTexture();
      this->mTex.enableMipmap();
      this->mTex.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
      this->mTex.generateMipmap();
    }
  }
  if (ImGui::Button("Remove image", ImVec2(100.f, 30.f))) {
    mTex.clear();
    image.clear();
  }

  this->colorPicker.createColorPicker(this->color);
}

const of3dPrimitive &SceneObject::getPrimitive() const {
  return *this->primitive;
}
