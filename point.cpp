#include "point.hpp"

Point::Point(double x, double y, double z)
  :x_(x), y_(y), z_(z)
{
}

double Point::GetX()
{
  return x_;
}

double Point::GetY()
{
  return y_;
}

double Point::GetZ()
{
  return z_;
}

void Point::SetX(double x)
{
  x_ = x;
}

void Point::SetY(double y)
{
  y_ = y;
}

void Point::SetZ(double z)
{
  z_ = z;
}
