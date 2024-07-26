#pragma once
struct DEAD_Vector {
  double x;
  double y;
};

class DEAD_Functions {
public:
  static double calDistance(double x1, double y1, double x2, double y2);
  static double calAngle(double x1, double y1, double x2, double y2);
  static DEAD_Vector calUnitVector(double angle);
};
