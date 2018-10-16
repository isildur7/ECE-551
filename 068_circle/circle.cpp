#include "circle.h"
#define PI 3.1415926535

Circle::Circle() : cen(), radius(1) {}
Circle::Circle(const Point p, const double rad) : cen(p), radius(rad) {}

void Circle::move(double dx, double dy) {
  Circle::cen.move(dx, dy);
}

/*double mod_square_root(double A, double X) {
  return pow((pow(A, 2) - pow(X, 2)), 0.5);
  }*/

double calculateY(double A, double B, double d) {
  double x = pow(A, 2) - pow(B, 2) + pow(d, 2);
  x = x / (2 * d * A);
  return x;
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double radA = fmax(Circle::radius, otherCircle.radius);
  double radB = fmin(Circle::radius, otherCircle.radius);

  double dist = Circle::cen.distanceFrom(otherCircle.cen);

  if (dist >= radA + radB) {
    return 0;
  }
  if (dist <= radA - radB) {
    return PI * pow(radB, 2);
  }

  double y1 = calculateY(radA, radB, dist);
  double y2 = calculateY(radB, radA, dist);

  double area = pow(radA, 2) * acos(y1);
  area += pow(radB, 2) * acos(y2);
  area -= 0.5 * sqrt((-dist + radA + radB) * (dist + radA + radB) * (dist + radA - radB) *
                     (dist - radA + radB));

  return area;
}
