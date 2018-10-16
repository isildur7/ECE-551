#ifndef __POINT_H__
#define __POINT_H__

class Point
{
 private:
  double x;
  double y;

 public:
  Point();
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
};
#endif
