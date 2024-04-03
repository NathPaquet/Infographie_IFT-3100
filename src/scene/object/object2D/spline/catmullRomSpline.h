#pragma once
#include "object2D.h"
class CatmullRomSpline : public Object2D {
public:
  CatmullRomSpline(const vector<glm::vec3> &controlPoints);
  void initMesh(const vector<glm::vec3> &controlPoints);
  void draw();
  void update();
  void addControlPoint(const glm::vec3 &controlPoint);
  void removeControlPoint(const glm::vec3 &controlPoint);
  void setControlPoint(const glm::vec3 &controlPoint, const glm::vec3 &newControlPoint);

private:
  int getNumSegments(const vector<glm::vec2> &points);
  float getT(float ti, const glm::vec2 &pi, const glm::vec2 &pj, float alpha);
  void calculateCatmullRomCurvePoints();
  vector<glm::vec2> calculateCatmullRomSplineBetweenFourPoints(const glm::vec2 &P0, const glm::vec2 &P1, const glm::vec2 &P2, const glm::vec2 &P3);

  vector<glm::vec2> controlPoints;
  vector<glm::vec2> curvePoints;
};
