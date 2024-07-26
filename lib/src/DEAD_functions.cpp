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
