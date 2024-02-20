#pragma once

#include "layouts/ColorPicker.h"
#include "ofMain.h"
#include "properties/Property.h"

class SceneObject {
public:
  ofVec3f position;
  ofColor color = ofColor::fromHsb(ofRandom(255), 255, 255);

  virtual void draw(bool isSelected) const;
  virtual void draw_properties();
  const of3dPrimitive &getPrimitive() const;
  std::map<std::string, std::unique_ptr<PropertyBase>> &getProperties();

protected:
  std::unique_ptr<of3dPrimitive> primitive;
  std::map<std::string, std::unique_ptr<PropertyBase>> properties;
  ofMesh mainMesh;
  ofTexture mTex;
  ofImage image;
  ColorPicker colorPicker;
};
