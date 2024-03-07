#pragma once

#include "layouts/ColorPicker.h"
#include "ofMain.h"
#include "properties/Property.h"

class SceneObject {
public:
  ofVec3f position;
  ofColor color = ofColor::fromHsb(ofRandom(255), 255, 255);
  SceneObject();
  virtual void draw(bool isSelected, bool isBoundingBoxEnable, bool isObjectAxisEnable);
  virtual void draw_properties();
  const of3dPrimitive &getPrimitive() const;
  void setPosition(ofVec3f vec);
  std::map<PROPERTY_ID, std::unique_ptr<PropertyBase>> &getProperties();

  template<typename T>
  T getPropertyValue(const PROPERTY_ID &propertyName) {
    return dynamic_cast<Property<T> *>(this->properties.at(propertyName).get())->getValue();
  }

  template<typename T>
  void addProperty(const PROPERTY_ID &propertyName, const T &initialValue) {
    this->properties.emplace(std::make_pair(propertyName, std::make_unique<Property<T>>(propertyName, initialValue)));
  }

protected:
  virtual void updateProperties();
  virtual void drawAxis();
  virtual void drawBoundingBox();
  std::unique_ptr<of3dPrimitive> primitive;
  std::map<PROPERTY_ID, std::unique_ptr<PropertyBase>> properties;
  ofMesh mainMesh;
  ofMaterial mMaterial;
  ofTexture mTex;
};
