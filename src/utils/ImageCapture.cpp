#include "ImageCapture.h"

ImageCapture::ImageCapture() {
    ofAddListener(ofEvents().update, this, &ImageCapture::update);
    ofLogNotice("ImageCapture") << "Listener to update added";
}

ImageCapture::~ImageCapture() {
    ofRemoveListener(ofEvents().update, this, &ImageCapture::update);
    ofLogNotice("ImageCapture") << "Listener to update removed";
}

void ImageCapture::startRecording(int interval, int duration) {
    if (!recordingStatus) {
        recordingStatus = true;
        startTime = ofGetElapsedTimeMillis();
        endTime = startTime + duration;
        this->interval = interval;
    }
}

bool ImageCapture::isRecording() {
    return recordingStatus;
}

void ImageCapture::update(ofEventArgs& event) {
    if (recordingStatus) {
        if (ofGetElapsedTimeMillis() < endTime) {
            if (ofGetElapsedTimeMillis() - lastExecutionTime >= interval) {
                addScreenshot();
                lastExecutionTime = ofGetElapsedTimeMillis();
            }
        }
        else {
            ofLogNotice("ImageCapture") << "interval has ended";
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
    ofLogNotice("ImageCapture") << "screenshot +1";

    ofImage screenshot;
    screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());

    screenshots.push_back(screenshot);
}

void ImageCapture::saveScreenshots(const string& path) {
    for (int i = 0; i < screenshots.size(); i++) {
        string filePath = path + to_string(i + 1) + ".png";
        screenshots.at(i).save(filePath);
    }
}
