#include <DEAD_functions.h>
#include <cmath>

double DEAD_Functions::calDistance(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
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



