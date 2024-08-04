#pragma once
#include "DEAD_zombie_movement_maps.h"
#include <map>
struct DEAD_Vector {
  double x;
  double y;
};

class DEAD_Functions {
public:
  static double calDistance(double x1, double y1, double x2, double y2);
  static double calDistance(const ZombieVector& vector);
  static double calAngle(double x1, double y1, double x2, double y2);
  static DEAD_Vector calUnitVector(double angle);
  static void normalizeVector(DEAD_Vector &vector);
  static void normalizeVector(ZombieVector &vector);
  static double boundNumber(double value, double min, double max);
  static void getRandomNumbersFromZeroToN(int n, std::map<int, bool>& returnMap, int returnSize);
};
