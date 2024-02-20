#pragma once
#include <string>

// Déclaration d'une classe de base polymorphique pour Property
class PropertyBase {
public:
  virtual ~PropertyBase() {}
  virtual std::string getId() const = 0;
};

template<typename T>
class Property : public PropertyBase {
public:
  Property(const std::string &id, const T &value):
      id(id), value(value) {}

  std::string getId() const override {
    return id;
  }

  T getValue() const;
  void setValue(T value);

private:
  T value;
  std::string id;
};

// DEFINITIONS

template<typename T>
T Property<T>::getValue() const {
  return this->value;
}

template<typename T>
void Property<T>::setValue(T value) {
  this->value = value;
}
