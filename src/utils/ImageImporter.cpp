#include "ImageImporter.h"

void ImageImporter::importImage(Property<ofImage> *property) {
  ofFileDialogResult result = ofSystemLoadDialog("Load file");
  if (result.bSuccess) {
    string pathToLoad = result.getPath();

    if (property->getValue().load(pathToLoad)) {
      property->setChanged(true);
      ofLogNotice("ofApp") << "Image loaded successfully from: " << pathToLoad;
    } else {
      ofLogError("ofApp") << "Failed to load image from: " << pathToLoad;
    }
  }
}
