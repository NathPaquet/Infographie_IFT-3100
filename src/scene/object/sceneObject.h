#pragma once

#include "layouts/ColorPicker.h"
#include "ofMain.h"
#include "properties/Property.h"

class SceneObject {
public:
  SceneObject();
  virtual void draw(bool isSelected, bool isBoundingBoxEnable, bool isObjectAxisEnable) = 0;
  const of3dPrimitive &getPrimitive() const;
  const ofVec3f &getPosition() const;
  virtual void setPosition(ofVec3f vec);
  virtual void setDraggingPositionOnObject(ofVec3f vec);
  virtual void stopDraggingObject();
  std::map<PROPERTY_ID, std::unique_ptr<PropertyBase>> &getProperties();
  virtual void displayObjectOptions();

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
  virtual void drawAxis() = 0;
  virtual void drawBoundingBox() = 0;

  std::unique_ptr<of3dPrimitive> primitive;
  std::map<PROPERTY_ID, std::unique_ptr<PropertyBase>> properties;
  ofVec3f position;
  glm::vec3 draggingPosition;
  ofMesh mainMesh;
  ofMaterial mMaterial;
  ofTexture mTex;
};
