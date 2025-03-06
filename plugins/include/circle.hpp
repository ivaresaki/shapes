#pragma once

#include "shape.hpp"

class Circle : public Shape
{
  private:
    double radius;
    double PI = 3.14159;

  public:
    Circle(double radius);
    ~Circle();

    double get_radius() const;

    double get_area() const;
    double get_perimeter() const;
    std::ostream& print(std::ostream& os) const;
};