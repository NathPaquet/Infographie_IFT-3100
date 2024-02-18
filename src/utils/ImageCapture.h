#pragma once

#include "ofMain.h"

class ImageCapture {
public:
  ImageCapture();
  ~ImageCapture();

  void takeScreenshot();
  void startRecording(int interval, int duration);
  bool isRecording();

private:
  std::vector<ofImage> screenshots;
  bool recordingStatus = false;
  int interval;
  int startTime;
  int endTime;
  int lastExecutionTime;

  void update(ofEventArgs &event);
  void addScreenshot();
  void saveScreenshots(const std::string &path);
};
