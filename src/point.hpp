#ifndef POINT_HPP
#define POINT_HPP

class Point
{
  public:
    Point(double x = 0.0, double y = 0.0, double z = 0.0);

    double GetX() const;
    double GetY() const;
    double GetZ() const;
    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);

  private:
    double x_;
    double y_;
    double z_;

};

#endif
