#include "catmullRomSpline.h"

#include "constants.h"
#include "primitive/Circle.h"

CatmullRomSpline::CatmullRomSpline(const glm::vec3 &startPoint, const glm::vec3 &endPoint) {
  glm::vec3 P0 = startPoint;
  glm::vec3 P3 = endPoint;
  glm::vec3 P1 = glm::vec3(P0.x + (P3.x - P0.x) / 5, P0.y, startPoint.z);
  glm::vec3 P2 = glm::vec3(P3.x - (P3.x - P0.x) / 5, P3.y, endPoint.z);

  this->controlPoints = {P0, P1, P2, P3};
  calculateCatmullRomCurvePoints();
  createMeshFromControlPoints();
}

void CatmullRomSpline::drawPreview(const glm::vec3 &startPoint, const glm::vec3 &endPoint) {
  glm::vec3 P0 = startPoint;
  glm::vec3 P3 = endPoint;
  glm::vec3 P1 = glm::vec3(P0.x + (P3.x - P0.x) / 5, P0.y, startPoint.z);
  glm::vec3 P2 = glm::vec3(P3.x - (P3.x - P0.x) / 5, P3.y, endPoint.z);

  vector<glm::vec3> controlPoints = {P0, P1, P2, P3};
  vector<glm::vec3> chainPoints = calculateCatmullRomSplineBetweenFourPoints(P0, P1, P2, P3);

  for (int i = 0; i < controlPoints.size(); ++i) {
    ofSetColor(ofColor::red);
    ofDrawCircle(controlPoints[i], Constants::POINT_RADIUS);
    ofPopStyle();
  }

  for (int i = 0; i < chainPoints.size() - 1; ++i) {
    ofDrawLine(chainPoints[i], chainPoints[i + 1]);
  }
}

void CatmullRomSpline::draw(bool isSelected, bool isBoundingBoxEnable, bool isObjectAxisEnable) {
  for (int i = 0; i < curvePoints.size() - 1; ++i) {
    ofDrawLine(curvePoints[i], curvePoints[i + 1]);
  }

  if (isSelected) {
    for (int i = 0; i < controlPoints.size(); ++i) {
      ofSetColor(ofColor::red);
      ofDrawCircle(controlPoints[i], Constants::POINT_RADIUS);
      ofPopStyle();
    }
  }
}

void CatmullRomSpline::setPosition(ofVec3f vec) {
  controlPoints[this->currentSelectedPointIndex] = vec;
  calculateCatmullRomCurvePoints();
}

void CatmullRomSpline::setDraggingPositionOnObject(ofVec3f vec) {
  SceneObject::setDraggingPositionOnObject(vec);

  // Get index of closest point to dragging position
  int closestPointIndex = -1;
  float minDistance = Constants::POINT_RADIUS;
  for (int i = 0; i < controlPoints.size(); ++i) {
    float distance = glm::distance(this->draggingPosition, controlPoints[i]);
    if (distance < minDistance) {
      minDistance = distance;
      closestPointIndex = i;
    }
  }
  this->currentSelectedPointIndex = closestPointIndex;
}

void CatmullRomSpline::releaseObjectFromDragging() {
  createMeshFromControlPoints();
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
    vector<glm::vec3> splinePoints = calculateCatmullRomSplineBetweenFourPoints(
        this->controlPoints[i],
        this->controlPoints[i + 1],
        this->controlPoints[i + 2],
        this->controlPoints[i + 3]);
    curvePoints.insert(curvePoints.end(), splinePoints.begin(), splinePoints.end());
  }
}

vector<glm::vec3> CatmullRomSpline::calculateCatmullRomSplineBetweenFourPoints(const glm::vec3 &P0, const glm::vec3 &P1, const glm::vec3 &P2, const glm::vec3 &P3) {
  int numPoints = Constants::CATMULL_ROM_NUM_POINTS;
  float alpha = Constants::CATMULL_ROM_ALPHA;

  vector<glm::vec3> points;

  float zValue = P0.z;
  glm::vec2 P0xy = glm::vec2(P0.x, P0.y);
  glm::vec2 P1xy = glm::vec2(P1.x, P1.y);
  glm::vec2 P2xy = glm::vec2(P2.x, P2.y);
  glm::vec2 P3xy = glm::vec2(P3.x, P3.y);

  float t0 = 0.0;
  float t1 = getT(t0, P0xy, P1xy, alpha);
  float t2 = getT(t1, P1xy, P2xy, alpha);
  float t3 = getT(t2, P2xy, P3xy, alpha);

  for (int i = 0; i < numPoints; ++i) {
    float t = ofMap(i, 0, numPoints - 1, t1, t2);
    auto A1 = (t1 - t) / (t1 - t0) * P0xy + (t - t0) / (t1 - t0) * P1xy;
    auto A2 = (t2 - t) / (t2 - t1) * P1xy + (t - t1) / (t2 - t1) * P2xy;
    auto A3 = (t3 - t) / (t3 - t2) * P2xy + (t - t2) / (t3 - t2) * P3xy;
    auto B1 = (t2 - t) / (t2 - t0) * A1 + (t - t0) / (t2 - t0) * A2;
    auto B2 = (t3 - t) / (t3 - t1) * A2 + (t - t1) / (t3 - t1) * A3;
    auto point = (t2 - t) / (t2 - t1) * B1 + (t - t1) / (t2 - t1) * B2;
    auto point3D = glm::vec3(point.x, point.y, zValue);
    points.push_back(point3D);
  }
  return points;
}

void CatmullRomSpline::createMeshFromControlPoints() {
  ofMesh mesh = ofMesh();
  size_t totalIndexNumber = 0;
  glm::vec3 firstControlPoints = this->controlPoints.at(0);

  for (const auto &controlPoint : controlPoints) {
    ofPushMatrix();
    ofTranslate(firstControlPoints);
    auto controlPointPrimitive = Circle(controlPoint - firstControlPoints, Constants::POINT_RADIUS);
    ofPopMatrix();

    for (auto &&vertex : controlPointPrimitive.getPrimitive().getMesh().getVertices()) {
      mesh.addVertex(glm::vec3(controlPointPrimitive.getPrimitive().getPosition().x + vertex.x, controlPointPrimitive.getPrimitive().getPosition().y + vertex.y, vertex.z));
    }

    for (auto &&index : controlPointPrimitive.getPrimitive().getMesh().getIndices()) {
      mesh.addIndex(index + totalIndexNumber);
    }
    totalIndexNumber += controlPointPrimitive.getPrimitive().getMesh().getVertices().size();
  }

  this->primitive = std::make_unique<of3dPrimitive>(of3dPrimitive(mesh));
  this->primitive->setPosition(this->controlPoints[0]);

  this->position = this->controlPoints[0];
}
