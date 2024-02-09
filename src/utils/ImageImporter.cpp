#include "ImageImporter.h"

void ImageImporter::importImage(ofImage &image) {
  ofFileDialogResult result = ofSystemLoadDialog("Load file");
  if (result.bSuccess) {
    string pathToLoad = result.getPath();

    if (image.load(pathToLoad)) {
      ofLogNotice("ofApp") << "Image loaded successfully from: " << pathToLoad;
    } else {
      ofLogError("ofApp") << "Failed to load image from: " << pathToLoad;
    }
  }
}
