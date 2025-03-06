#pragma once

#include "shape.hpp"

class Rectangle : public Shape
{
  private:
    double width;
    double height;

  public:
    Rectangle(double width, double height);
    virtual ~Rectangle();

    double get_width() const;
    double get_height() const;

    double get_area() const;
    std::ostream& print(std::ostream& os) const;
};