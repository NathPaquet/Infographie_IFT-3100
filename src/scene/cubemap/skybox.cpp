#include "skybox.h"

Skybox::Skybox() {
  this->skyboxShader.load("shaders/skybox.vert", "shaders/skybox.frag");
}

void Skybox::loadTexture(const string &texturePath) {
  this->cubemapTexture.loadCubemapTextures(texturePath);
}

void Skybox::draw(float size) {
  ofEnableArbTex();
  //
  // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  //
  // glEnable(GL_TEXTURE_CUBE_MAP_ARB);
  //
  skyboxShader.begin();
  // glDisable(GL_DEPTH_TEST);
  ofDisableDepthTest();
  // glActiveTexture(GL_TEXTURE0);
  // cubemapTexture.bind();
  //
  skyboxShader.setUniform1i("skybox", 0);
  // glMatrixMode(GL_MODELVIEW);
  // glPushMatrix();
  // ofMesh box = ofMesh::box(size, size, size, 1, 1, 1);
  ofDrawBox(0, 0, 0, size); // TODO : Position de la caméra
  //  drawSkybox(0, 0, 0, 100, 100, 100);

  // cubemapTexture.unbind();
  skyboxShader.end();
  //
  // glDisable(GL_TEXTURE_CUBE_MAP_ARB);
  //
  // glEnable(GL_DEPTH_TEST);
  ofEnableDepthTest();
  //  glPopMatrix();
  //
  ofDisableArbTex();
}

void Skybox::drawSkybox(float x, float y, float z, float width, float height, float length) {
  // Center the Skybox around the given x,y,z position
  x = x - width / 2;
  y = y - height / 2;
  z = z - length / 2;

  // Draw Front side

  glBegin(GL_QUADS);
  glVertex3f(x, y, z + length);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(x, y + height, z + length);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(x + width, y + height, z + length);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(x + width, y, z + length);
  glTexCoord2f(0.0f, 0.0f);
  glEnd();

  // Draw Back side

  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(x + width, y, z);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(x + width, y + height, z);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(x, y + height, z);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(x, y, z);
  glEnd();

  // Draw Left side

  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(x, y + height, z);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(x, y + height, z + length);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(x, y, z + length);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(x, y, z);
  glEnd();

  // Draw Right side

  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(x + width, y, z);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(x + width, y, z + length);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(x + width, y + height, z + length);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(x + width, y + height, z);
  glEnd();

  // Draw Up side

  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(x + width, y + height, z);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(x + width, y + height, z + length);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(x, y + height, z + length);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(x, y + height, z);
  glEnd();

  // Draw Down side

  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(x, y, z);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(x, y, z + length);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(x + width, y, z + length);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(x + width, y, z);
  glEnd();
}
