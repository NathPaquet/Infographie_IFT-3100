#pragma once

#include <array>
#include <string>

class ImageFormatDropdown {
public:
  void create();
  std::string getSelectedFormat() const;

private:
  const std::array<std::string, 3> formats = {"png", "jpg", "bmp"};
  std::string selectedFormat = formats.front();
};
