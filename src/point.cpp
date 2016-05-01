#include "point.hpp"

/* using namespace std; */

Point::Point(double x, double y, double z)
  : x_(x), y_(y), z_(z)
{
}

double Point::GetX() const
{
  return x_;
}

double Point::GetY() const
{
  return y_;
}

double Point::GetZ() const
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
