#include <DEAD_functions.h>
#include <algorithm>
#include <cmath>
#include <map>


double DEAD_Functions::calDistance(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double DEAD_Functions::getDegreeFromZeroTo360(double degree) {
  while (degree < 0) {
    degree += 360;
  }

  while (degree > 360) {
    degree -= 360;
  }

  return degree;
}


PointAndTriangleReturn DEAD_Functions::checkPointAndTriangle(DEAD_Vector point, DEAD_Triangle triangle) {
  DEAD_Triangle triangle1, triangle2, triangle3;

  triangle1.point1 = point;
  triangle1.point2 = triangle.point1;
  triangle1.point3 = triangle.point2;

  triangle2.point1 = point;
  triangle2.point2 = triangle.point2;
  triangle2.point3 = triangle.point3;

  triangle3.point1 = point;
  triangle3.point2 = triangle.point3;
  triangle3.point3 = triangle.point1;

  double triangle1Area = fabs(DEAD_Functions::getTriangleArea(triangle1));
  double triangle2Area = fabs(DEAD_Functions::getTriangleArea(triangle2));
  double triangle3Area = fabs(DEAD_Functions::getTriangleArea(triangle3));
  double triangleArea = fabs(DEAD_Functions::getTriangleArea(triangle));
  
  double trianglesAreaSum = triangle1Area + triangle2Area + triangle3Area;
  double delta = 0;
  if (triangleArea == trianglesAreaSum) {
    if (triangle1Area == 0 || triangle2Area == 0 || triangle3Area == 0) {
      return PointAndTriangleReturn::POINT_ON_TRIANGLE;
    } else {
      return PointAndTriangleReturn::POINT_IN_TRIANGLE;
    }
  } else {
    return PointAndTriangleReturn::POINT_OUT_OF_TRIANGLE;
  }
}

double DEAD_Functions::getTriangleArea(DEAD_Triangle triangle) {
  return (0.5)*((triangle.point1.x*(triangle.point2.y-triangle.point3.y))+
                    triangle.point2.x*(triangle.point3.y-triangle.point1.y)+
                    triangle.point3.x*(triangle.point1.y-triangle.point2.y));
}

static DEAD_LineEquation getLineEquationFromPoints(DEAD_Vector point1, DEAD_Vector point2) {
  DEAD_LineEquation equation;
  // y = mx+k
  // mx-y+k=0
  equation.a = (point2.y-point1.y)/(point2.x-point1.x);
  equation.c = point1.y-equation.a*point1.x;
  equation.b = -1;
  return equation; 
}

double DEAD_Functions::calAngle(double x1, double y1, double x2, double y2) {
  double relX = x2 - x1;
  double relY = y2 - y1;

  double rad = atan(relY / relX);
  double degree = rad * (180.0 / M_PI);

  if (degree == 0) {
    if (relX >= 0)
      return 0;
    else if (relX < 0)
      return 180;
  } else {
    if (relX < 0) {
      return degree + 180;
    } else {
      return degree;
    }
  }
  return 0.0;
}

DEAD_Vector DEAD_Functions::calUnitVector(double angle) {
  DEAD_Vector returnVector; 
  if (angle == 0) {
    returnVector.x = 1;
    returnVector.y = 0;
    return returnVector;
  } else if (angle == 180) {
    returnVector.x = -1;
    returnVector.y = 0;
    return returnVector;
  } else if (angle == 90) {
    returnVector.x = 0;
    returnVector.y = 1;
    return returnVector;
  } else if (angle == 270) {
    returnVector.x = 0;
    returnVector.y = -1;
    return returnVector;
  }

  returnVector.x = cos(angle/180*M_PI);
  returnVector.y = sin(angle/180*M_PI);
  return returnVector;
}

void DEAD_Functions::normalizeVector(DEAD_Vector& vector) {
  double distance = DEAD_Functions::calDistance(0, 0, vector.x, vector.y);
  if (distance == 0) return;
  vector.x = vector.x / distance;
  vector.y = vector.y / distance;
}

void DEAD_Functions::normalizeVector(ZombieVector &vector) {
  double distance = DEAD_Functions::calDistance(0, 0, vector.vectorX, vector.vectorY);
  if (distance == 0) return;
  vector.vectorX = vector.vectorX / distance;
  vector.vectorY = vector.vectorY / distance;
}

double DEAD_Functions::calDistance(const ZombieVector& vector) {
  return DEAD_Functions::calDistance(0, 0, vector.vectorX, vector.vectorY);
}

double DEAD_Functions::boundNumber(double value, double min, double max) {
  if (value < min) return min;
  if (value > max) return max;
  return value;
}

void DEAD_Functions::getRandomNumbersFromZeroToN(int n, std::map<int, bool>& returnMap, int returnSize) {
  int temp[n];
  for (int i = 0; i < n; i++) {
    temp[i] = i;
    returnMap.insert(std::pair<int, bool>(i, false));
  }
  std::random_shuffle(temp, temp+n);
  for (int i = 0; i < returnSize; i++) {
    returnMap[i] = true; 
  }
}

bool DEAD_Functions::linesIntersection(DEAD_Line& line1, DEAD_Line& line2, DEAD_Vector& intersectPoint) {
  double x1 = line1.point1.x;
  double x2 = line1.point2.x;
  double x3 = line2.point1.x;
  double x4 = line2.point2.x;

  double y1 = line1.point1.y;
  double y2 = line1.point2.y;
  double y3 = line2.point1.y;
  double y4 = line2.point2.y;

  double a = (x4-x3)*(y3-y1)-(y4-y3)*(x3-x1);
  double b = (x4-x3)*(y2-y1)-(y4-y3)*(x2-x1);
  double c = (x2-x1)*(y3-y1)-(y2-y1)*(x3-x1);
  
  if (b==0) { return false; }

  double alpha = a/b;
  double beta = c/b;

  if ((alpha < 0 || alpha > 1) || (beta < 0 || beta > 1)) {
    return false;
  }

  intersectPoint.x = x1+alpha*(x2-x1);
  intersectPoint.y = y1+alpha*(y2-y1);
  return true;
}





