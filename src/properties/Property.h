#pragma once
#include <string>

struct LineParameter {
  bool shouldDrawWireFrame;
  float lineThickness;

  bool operator==(const LineParameter &other) {
    return this->lineThickness == other.lineThickness && this->shouldDrawWireFrame == other.shouldDrawWireFrame;
  }
};

enum class PROPERTY_ID {
  // Place common properties here
  COLOR,
  IMAGE_IMPORT,
  // Place object specific properties here
  SIZE,
  RADIUS,
  WIDTH,
  HEIGHT,
  ANGLE_X,
  ANGLE_Y,
  ANGLE_Z,
  SHOW_WIREFRAME,
  RATIO,
  CATMULL_ROM_ALPHA,
  TEXTURE,
};

static inline const char *toString(PROPERTY_ID propertyId) {
  switch (propertyId) {
    case PROPERTY_ID::SIZE:
      return "Size";
    case PROPERTY_ID::WIDTH:
      return "Width";
    case PROPERTY_ID::RADIUS:
      return "Radius";
    case PROPERTY_ID::HEIGHT:
      return "Height";
    case PROPERTY_ID::COLOR:
      return "Color";
    case PROPERTY_ID::IMAGE_IMPORT:
      return "Image Import";
    case PROPERTY_ID::ANGLE_X:
      return "Angle X";
    case PROPERTY_ID::ANGLE_Y:
      return "Angle Y";
    case PROPERTY_ID::ANGLE_Z:
      return "Angle Z";
    case PROPERTY_ID::SHOW_WIREFRAME:
      return "Show only wireframe";
    case PROPERTY_ID::RATIO:
      return "Ratio";
    case PROPERTY_ID::CATMULL_ROM_ALPHA:
      return "Catmull Rom Alpha";
    case PROPERTY_ID::TEXTURE:
      return "Texture";
    default:
      return "Unknown";
  }
}
// Déclaration d'une classe de base polymorphique pour Property
class PropertyBase {
public:
  virtual ~PropertyBase() {}
  PropertyBase(PROPERTY_ID id):
      id(id) {}
  virtual PROPERTY_ID getId() {
    return this->id;
  }
  void setChanged(bool changed) {
    this->changed = changed;
  }
  bool isValueChanged() {
    return this->changed;
  }

protected:
  PROPERTY_ID id;
  bool changed = false;
};

template<typename T>
class Property : public PropertyBase {
public:
  Property(const PROPERTY_ID &id, const T &value):
      PropertyBase(id),
      value(value) {}

  T &getValue();
  void setValue(T value);

private:
  T value;
};

// DEFINITIONS

template<typename T>
T &Property<T>::getValue() {
  return this->value;
}

template<typename T>
void Property<T>::setValue(T value) {
  if (this->value == value) {
    return;
  }

  this->value = value;
  this->setChanged(true);
}
