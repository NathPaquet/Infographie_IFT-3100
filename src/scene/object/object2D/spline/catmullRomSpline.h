#pragma once
#include "object2D.h"
class CatmullRomSpline : public Object2D {
public:
  CatmullRomSpline(const glm::vec3 &startPoint, const glm::vec3 &endPoint);
  static void drawPreview(const glm::vec3 &startPoint, const glm::vec3 &endPoint);
  void draw(bool isSelected, bool isBoundingBoxEnable, bool isObjectAxisEnable) override;

private:
  int getNumSegments(const vector<glm::vec3> &points);
  static float getT(float ti, const glm::vec2 &pi, const glm::vec2 &pj, float alpha);
  void calculateCatmullRomCurvePoints();
  static vector<glm::vec3> calculateCatmullRomSplineBetweenFourPoints(const glm::vec3 &P0, const glm::vec3 &P1, const glm::vec3 &P2, const glm::vec3 &P3);
  void initMeshFromControlPoints();

  vector<glm::vec3> controlPoints;
  vector<glm::vec3> curvePoints;
};
