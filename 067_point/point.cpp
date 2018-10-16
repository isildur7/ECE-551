#include "point.h"

#include <math.h>

Point ::Point() : x(0), y(0) {}
Point ::Point(double x, double y) : x(x), y(y) {}
void Point ::move(double dx, double dy) {
  Point::x += dx;
  Point::y += dy;
}

double Point::distanceFrom(const Point & p) {
  double d_x = pow((Point::x - p.x), 2);
  double d_y = pow((Point::y - p.y), 2);
  return pow(d_x + d_y, 0.5);
}
