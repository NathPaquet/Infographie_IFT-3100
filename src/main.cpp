#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {
  ofGLWindowSettings settings;
#if defined(TARGET_OSX)
  settings.setGLVersion(3, 2);
#else
  settings.setGLVersion(3, 2);
#endif

  settings.setSize(1280, 720);
  ofCreateWindow(settings);
  ofRunApp(new ofApp());
}
