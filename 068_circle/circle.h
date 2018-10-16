#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include <math.h>

#include "point.h"

class Circle
{
 private:
  Point cen;
  const double radius;

 public:
  Circle();
  Circle(const Point p, const double rad);
  void move(double dx, double dy);
  double intersectionArea(const Circle & othercircle);
};
#endif
