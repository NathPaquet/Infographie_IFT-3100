#pragma once
#include "object2D.h"
class CatmullRomSpline : public Object2D {
public:
  CatmullRomSpline(const vector<glm::vec3> &controlPoints);
  static void drawPreview(const glm::vec3 &startPoint, const glm::vec3 &endPoint);

private:
  int getNumSegments(const vector<glm::vec3> &points);
  float getT(float ti, const glm::vec2 &pi, const glm::vec2 &pj, float alpha);
  void calculateCatmullRomCurvePoints();
  vector<glm::vec2> calculateCatmullRomSplineBetweenFourPoints(const glm::vec2 &P0, const glm::vec2 &P1, const glm::vec2 &P2, const glm::vec2 &P3);

  vector<glm::vec3> controlPoints;
  vector<glm::vec3> curvePoints;
};
