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
  HEIGHT,
  ANGLES,
  SHOW_WIREFRAME,
  RATIO,
};

static inline const char *toString(PROPERTY_ID propertyId) {
  switch (propertyId) {
    case PROPERTY_ID::SIZE:
      return "Size";
    case PROPERTY_ID::RADIUS:
      return "Radius";
    case PROPERTY_ID::HEIGHT:
      return "Height";
    case PROPERTY_ID::COLOR:
      return "Color";
    case PROPERTY_ID::IMAGE_IMPORT:
      return "Image Import";
    case PROPERTY_ID::ANGLES:
      return "Angles";
    case PROPERTY_ID::SHOW_WIREFRAME:
      return "Line thickness";
    case PROPERTY_ID::RATIO:
      return "Ratio";
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
