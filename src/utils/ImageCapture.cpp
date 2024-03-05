#include "ImageCapture.h"

ImageCapture::ImageCapture() {
  ofAddListener(ofEvents().update, this, &ImageCapture::update);
}

ImageCapture::~ImageCapture() {
  ofRemoveListener(ofEvents().update, this, &ImageCapture::update);
}

void ImageCapture::takeScreenshot() {
  ofFileDialogResult result = ofSystemSaveDialog("default", "Save Image");

  if (result.bSuccess) {
    ofImage screenshot;
    screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());

    string filePath = result.getPath() + "." + imageFormat;
    screenshot.save(filePath);
  }
}

void ImageCapture::startRecording(int interval, int duration) {
  if (!recordingStatus) {
    recordingStatus = true;
    startTime = ofGetElapsedTimeMillis();
    endTime = startTime + duration;
    this->interval = interval;
  }
}

void ImageCapture::setImageFormat(const std::string &imageFormat) {
  this->imageFormat = imageFormat;
}

bool ImageCapture::isRecording() {
  return recordingStatus;
}

void ImageCapture::update(ofEventArgs &event) {
  if (recordingStatus) {
    if (ofGetElapsedTimeMillis() < endTime) {
      if (ofGetElapsedTimeMillis() - lastExecutionTime >= interval) {
        addScreenshot();
        lastExecutionTime = ofGetElapsedTimeMillis();
      }
    } else {
      recordingStatus = false;
      ofFileDialogResult result = ofSystemSaveDialog("default", "Save Image");

      if (result.bSuccess) {
        saveScreenshots(result.getPath());
      }

      screenshots.clear();
    }
  }
}

void ImageCapture::addScreenshot() {
  ofImage screenshot;
  screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());

  screenshots.push_back(screenshot);
}

void ImageCapture::saveScreenshots(const string &path) {
  for (int i = 0; i < screenshots.size(); i++) {
    string filePath = path + to_string(i + 1) + "." + imageFormat;
    screenshots.at(i).save(filePath);
  }
}
