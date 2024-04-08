#include "catmullRomSpline.h"

#include "constants.h"

void CatmullRomSpline::drawPreview(const glm::vec3 &startPoint, const glm::vec3 &endPoint) {
  glm::vec3 P0 = startPoint;
  glm::vec3 P1 = glm::vec3(startPoint.x + 100, startPoint.y + 100, startPoint.z);
  glm::vec3 P2 = glm::vec3(endPoint.x - 100, endPoint.y - 100, endPoint.z);
  glm::vec3 P3 = endPoint;
}

int CatmullRomSpline::getNumSegments(const vector<glm::vec3> &points) {
  return points.size() - (Constants::CATMULL_ROM_QUADRUPLE_SIZE - 1);
}

float CatmullRomSpline::getT(float ti, const glm::vec2 &pi, const glm::vec2 &pj, float alpha) {
  float xi = pi.x;
  float yi = pi.y;
  float xj = pj.x;
  float yj = pj.y;
  float l = sqrt(pow(xj - xi, 2) + pow(yj - yi, 2));

  return ti + pow(l, alpha);
}

void CatmullRomSpline::calculateCatmullRomCurvePoints() {
  this->curvePoints.clear();

  for (int i = 0; i < getNumSegments(this->controlPoints); ++i) {
    vector<glm::vec2> splinePoints = calculateCatmullRomSplineBetweenFourPoints(
        this->controlPoints[i],
        this->controlPoints[i + 1],
        this->controlPoints[i + 2],
        this->controlPoints[i + 3]);
    curvePoints.insert(curvePoints.end(), splinePoints.begin(), splinePoints.end());
  }
}

vector<glm::vec2> CatmullRomSpline::calculateCatmullRomSplineBetweenFourPoints(const glm::vec2 &P0, const glm::vec2 &P1, const glm::vec2 &P2, const glm::vec2 &P3) {
  int numPoints = Constants::CATMULL_ROM_NUM_POINTS;
  float alpha = Constants::CATMULL_ROM_ALPHA;

  vector<glm::vec2> points;

  float t0 = 0.0;
  float t1 = getT(t0, P0, P1, alpha);
  float t2 = getT(t1, P1, P2, alpha);
  float t3 = getT(t2, P2, P3, alpha);

  for (int i = 0; i < numPoints; ++i) {
    float t = ofMap(i, 0, numPoints - 1, t1, t2);
    auto A1 = (t1 - t) / (t1 - t0) * P0 + (t - t0) / (t1 - t0) * P1;
    auto A2 = (t2 - t) / (t2 - t1) * P1 + (t - t1) / (t2 - t1) * P2;
    auto A3 = (t3 - t) / (t3 - t2) * P2 + (t - t2) / (t3 - t2) * P3;
    auto B1 = (t2 - t) / (t2 - t0) * A1 + (t - t0) / (t2 - t0) * A2;
    auto B2 = (t3 - t) / (t3 - t1) * A2 + (t - t1) / (t3 - t1) * A3;
    auto point = (t2 - t) / (t2 - t1) * B1 + (t - t1) / (t2 - t1) * B2;
    points.push_back(point);
  }
  return points;
}
